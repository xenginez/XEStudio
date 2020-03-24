#include "FSMGraphicsScene.h"

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
													 if( auto machine = GetStateMachine() )
													 {
														 auto handle = machine->AddState( val );

														 auto pos = GetGraphicsView()->mapToScene( GetGraphicsView()->mapFromGlobal( QCursor::pos() ) );

														 machine->GetState( handle )->SetPosition( XE::Vec2( pos.x(), pos.y() ) );

														 ResetGraphics();
													 }
												 } );

										AddStateMenu( m, val );
									}
									else if( val->IsAbstract() == false )
									{
										auto action = menu->addAction( QString::fromUtf8( val->GetName().ToCString() ) );
										connect( action, &QAction::triggered, [this, val]()
												 {
													 if( auto machine = GetStateMachine() )
													 {
														 auto handle = machine->AddState( val );
														 
														 auto pos = GetGraphicsView()->mapToScene( GetGraphicsView()->mapFromGlobal( QCursor::pos() ) );

														 machine->GetState( handle )->SetPosition( XE::Vec2( pos.x(), pos.y() ) );

														 ResetGraphics();
													 }
												 } );
									}
								} );
	}
}

void FSMGraphicsScene::ResetGraphics()
{
	this->clear();

	_Items.clear();

	const auto & states = GetStateMachine()->GetAllState();

	for( const auto & state : states )
	{
		if( state )
		{
			state->SetStateMachine( GetStateMachine() );

			auto item = new FSMGraphicsItem();
			item->SetState( state );
			this->addItem( item );
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
			}
		}
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

			QLineF line;
			line.setP1( QPointF( state->GetPosition().x + FSMGraphicsItem::Radius, state->GetPosition().y + FSMGraphicsItem::Radius ) );
			line.setP2( GetGraphicsView()->mapToScene( GetGraphicsView()->mapFromGlobal( QCursor::pos() ) ) );
			_Socket->SetLine( line );

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
