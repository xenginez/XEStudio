#include "FSMGraphicsScene.h"

#include <ogdf/basic/Graph.h>
#include <ogdf/basic/GraphAttributes.h>
#include <ogdf/layered/SugiyamaLayout.h>
#include <ogdf/layered/FastHierarchyLayout.h>

#include "GraphicsView.h"
#include "GraphicsWidget.h"
#include "FSMGraphicsItem.h"
#include "FSMGraphicsSocket.h"

FSMGraphicsScene::FSMGraphicsScene( QObject * parent /*= nullptr */ )
	:GraphicsScene( parent ), _Socket( nullptr )
{

}

FSMGraphicsScene::~FSMGraphicsScene()
{

}

void FSMGraphicsScene::contextMenuEvent( QGraphicsSceneContextMenuEvent * contextMenuEvent )
{
	if( selectedItems().size() == 0 )
	{
		QMenu menu;

		auto add_state = menu.addMenu( tr( "add state" ) );
		AddStateMenu( add_state, XE::State::GetMetaClassStatic() );
		auto update_state = menu.addAction( tr( "update state" ) );
		connect( update_state, &QAction::triggered, this, &FSMGraphicsScene::ResetGraphics );

		menu.exec( QCursor::pos() );
	}
	else
	{
		QGraphicsScene::contextMenuEvent( contextMenuEvent );
	}
}

XE::StateMachinePtr FSMGraphicsScene::GetStateMachine() const
{
	return SP_CAST<XE::StateMachine>( GetGraphicsView()->GetGraphicsWidget()->GetAIModule() );
}

void FSMGraphicsScene::AddStateMenu( QMenu * menu, const XE::IMetaClassPtr & cls )
{
	if( cls->GetDerivedClassSize() )
	{
		cls->VisitDerivedClass( [&]( XE::IMetaClassPtr val )
								{
									if( val->IsAbstract() && val->GetDerivedClassSize() )
									{
										auto m = menu->addMenu( QString::fromUtf8( val->GetName().ToCString() ) );
										AddStateMenu( m, val );
									}
									else if( val->IsAbstract() == false && val->GetDerivedClassSize() )
									{
										auto m = menu->addMenu( QString::fromUtf8( val->GetName().ToCString() ) );

										connect( m->menuAction() , &QAction::triggered, [this, val]()
												 {
													 ResetGraphics();
												 } );

										AddStateMenu( m, val );
									}
									else if( val->IsAbstract() == false )
									{
										auto action = menu->addAction( QString::fromUtf8( val->GetName().ToCString() ) );
										connect( action, &QAction::triggered, [this, val]()
												 {
													 ResetGraphics();
												 } );
									}
								} );
	}
}

void FSMGraphicsScene::ResetGraphics()
{
	this->clear();

	_Items.clear();

	QMap<XE::StateHandle, ogdf::NodeElement * > nodes;

	ogdf::Graph graph;
	ogdf::GraphAttributes attr( graph,
							   ogdf::GraphAttributes::nodeGraphics | ogdf::GraphAttributes::edgeGraphics |
							   ogdf::GraphAttributes::nodeLabel | ogdf::GraphAttributes::edgeStyle |
							   ogdf::GraphAttributes::nodeStyle | ogdf::GraphAttributes::nodeTemplate );

	const auto & states = GetStateMachine()->GetAllState();
	for( const auto & state : states )
	{
		if( state )
		{
			state->SetStateMachine( GetStateMachine() );

			ogdf::NodeElement * node = graph.newNode();
			attr.width( node ) = FSMGraphicsItem::Radius;
			attr.height( node ) = FSMGraphicsItem::Radius;

			auto item = new FSMGraphicsItem();

			item->SetState( state );
			this->addItem( item );
			nodes.insert( state->GetHandle(), node );
			_Items.insert( state->GetHandle(), item );
		}
	}

	for( auto it = _Items.begin(); it != _Items.end(); ++it )
	{
		if( auto state = GetStateMachine()->GetState( it.key() ) )
		{
			const auto & conditions = state->GetConditions();
			for( const auto & c : conditions )
			{
				c->SetAIModule( GetStateMachine() );

				auto socket = new FSMGraphicsSocket();
				socket->SetCondition( c );
				socket->SetLastItem( it.value() );
				socket->SetNextItem( _Items[c->GetNextStateHandle()] );
				socket->SetLine( { it.value()->pos() + QPointF( FSMGraphicsItem::Radius,FSMGraphicsItem::Radius ),
								 _Items[c->GetNextStateHandle()]->pos() + QPointF( FSMGraphicsItem::Radius,FSMGraphicsItem::Radius ) } );
				this->addItem( socket );

				graph.newEdge( nodes[it.key()], nodes[c->GetNextStateHandle()] );
			}
		}
	}


	ogdf::SugiyamaLayout layout;

	ogdf::FastHierarchyLayout * ohl = new ogdf::FastHierarchyLayout;
	ohl->layerDistance( 30 );
	ohl->nodeDistance( 25 );
	layout.setLayout( ohl );

	layout.call( attr );

	for( auto it = nodes.begin(); it != nodes.end(); ++it )
	{
		_Items[it.key()]->setPos( attr.x( it.value() ), attr.y( it.value() ) );
	}
}

void FSMGraphicsScene::AddCondition( XE::StateHandle handle, const XE::IMetaClassPtr & cls )
{
	if( auto condition = cls->ConstructPtr().Value<XE::ConditionPtr>() )
	{
		if( auto state = GetStateMachine()->GetState( handle ) )
		{
			state->AddConditions( condition );

			_Socket = new FSMGraphicsSocket();

			_Socket->SetCondition( condition );
			_Socket->SetLastItem( _Items[handle.GetValue()] );
			_Socket->SetNextItem( nullptr );

			this->addItem( _Socket );
		}
	}
}

void FSMGraphicsScene::mouseMoveEvent( QGraphicsSceneMouseEvent * mouseEvent )
{
	if( _Socket )
	{
		auto line = _Socket->GetLine();

		QTransform transform;
		auto item = dynamic_cast< FSMGraphicsItem * >( this->itemAt( mouseEvent->scenePos(), transform ) );
		if( item )
		{
			line.setP2( item->boundingRect().center() + item->pos() );
		}
		else
		{
			line.setP2( mouseEvent->scenePos() );
		}

		_Socket->SetLine( line );
		_Socket->update();
	}

	this->update();

	GraphicsScene::mouseMoveEvent( mouseEvent );
}

void FSMGraphicsScene::mousePressEvent( QGraphicsSceneMouseEvent * mouseEvent )
{
	if( _Socket )
	{
		QTransform transform;
		auto item = dynamic_cast< FSMGraphicsItem * >( this->itemAt( mouseEvent->scenePos(), transform ) );
		if( item )
		{
			_Socket->SetNextItem( item );
			_Socket->GetCondition()->SetNextStateHandle( item->GetState()->GetHandle() );
		}
		else
		{
			dynamic_cast< FSMGraphicsItem * >( _Socket->GetLastItem() )->GetState()->RemoveConditions( _Socket->GetCondition() );
			this->removeItem( _Socket );
			delete _Socket;
		}

		_Socket = nullptr;
	}

	GraphicsScene::mousePressEvent( mouseEvent );
}
