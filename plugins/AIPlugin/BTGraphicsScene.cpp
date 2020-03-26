#include "BTGraphicsScene.h"

#include "AIDockWidget.h"
#include "GraphicsView.h"
#include "GraphicsWidget.h"
#include "BTGraphicsSocket.h"

BTGraphicsScene::BTGraphicsScene( QObject * parent /*= nullptr */ )
	:GraphicsScene( parent ), _SelectItem( nullptr )
{

}

BTGraphicsScene::~BTGraphicsScene()
{

}

XE::BehaviorTreePtr BTGraphicsScene::GetBehaviorTree() const
{
	return DP_CAST<XE::BehaviorTree>( GetGraphicsView()->GetGraphicsWidget()->GetAIModule() );
}

void BTGraphicsScene::ResetGraphics()
{
	clear();

	_Nodes.clear();

	if( GetBehaviorTree()->GetRoot() != XE::NodeHandle::Invalid )
	{
		if( auto root = GetBehaviorTree()->GetNode( GetBehaviorTree()->GetRoot() ) )
		{
			int x = 0;
			AddNode( root, 0, x );
			AddSocket( root );
		}
	}
}

void BTGraphicsScene::mousePressEvent( QGraphicsSceneMouseEvent * event )
{
	if( event->modifiers() == Qt::KeyboardModifier::ControlModifier )
	{
		QTransform transform;
		auto item = this->itemAt( event->scenePos(), transform );
		if( item != nullptr )
		{
			_SelectItem = dynamic_cast< BTGraphicsItem * >( item );
		}
	}

	GraphicsScene::mousePressEvent( event );
}

void BTGraphicsScene::mouseReleaseEvent( QGraphicsSceneMouseEvent * event )
{
	if( _SelectItem )
	{
		QTransform transform;
		auto item = this->itemAt( event->scenePos(), transform );
		if( item != nullptr )
		{
			GetBehaviorTree()->SwapNodeHandle( _SelectItem->GetNode()->GetHandle(), dynamic_cast< BTGraphicsItem * >( item )->GetNode()->GetHandle() );
			ResetGraphics();
		}

		_SelectItem = nullptr;
	}

	GraphicsScene::mouseReleaseEvent( event );
}

void BTGraphicsScene::contextMenuEvent( QGraphicsSceneContextMenuEvent * event )
{
	if( this->selectedItems().size() == 0 )
	{
		QMenu menu;

		if( GetBehaviorTree()->GetRoot() == XE::NodeHandle::Invalid )
		{
			auto node_menu = menu.addMenu( tr( "node" ) );
			AddNodeAction( node_menu, XE::ClassID<XE::Node>::Get() );
		}

		auto update_action = menu.addAction( tr( "update" ) );
		connect( update_action, &QAction::triggered, [this]()
				 {
					 ResetGraphics();
				 } );

		menu.exec( QCursor::pos() );
	}
	else
	{
		GraphicsScene::contextMenuEvent( event );
	}
}

int BTGraphicsScene::CalcMaxFloor( const XE::NodePtr & node, int floor )
{
	if( auto comp_node = DP_CAST<XE::CompositeNode>( node ) )
	{
		int ff = floor;

		for( auto handle : comp_node->GetChildren() )
		{
			int f = CalcMaxFloor( GetBehaviorTree()->GetNode( handle ), floor + 1 );
			ff = f > ff ? f : ff;
		}

		return ff;
	}
	else if( auto dec_node = DP_CAST<XE::DecoratorNode>( node ) )
	{
		if( dec_node->GetChild() )
		{
			return CalcMaxFloor( GetBehaviorTree()->GetNode( dec_node->GetChild() ), floor + 1 );
		}
	}
	else if( auto dec_node = DP_CAST<XE::ConditionNode>( node ) )
	{
		if( dec_node->GetChild() )
		{
			return CalcMaxFloor( GetBehaviorTree()->GetNode( dec_node->GetChild() ), floor + 1 );
		}
	}

	return floor;
}

BTGraphicsItem * BTGraphicsScene::AddNode( const XE::NodePtr & node, int floor, int & x )
{
	if( node == nullptr )
	{
		return nullptr;
	}

	node->SetBehaviorTree( GetBehaviorTree() );

	if( auto coms_node = DP_CAST<XE::CompositeNode>( node ) )
	{
		if( !coms_node->GetChildren().empty() )
		{
			QVector< BTGraphicsItem *> children;

			for( auto handle : coms_node->GetChildren() )
			{
				if ( GetBehaviorTree()->GetNode( handle ) )
				{
					children.push_back( AddNode( GetBehaviorTree()->GetNode( handle ), floor + 1, x ) );
				}
			}

			int left = x;
			int right = 0;

			for( auto child : children )
			{
				left = std::min( static_cast< int >( child->boundingRect().left() ), left );
				right = std::max( static_cast< int >( child->boundingRect().right() ), right );
			}

			auto g_node = new BTGraphicsItem();
			g_node->setBoundingRect( {
				qreal( left + ( ( right - left ) / 2 ) - ( BTGraphicsItem::Width / 2 ) ),
				qreal( floor * ( BTGraphicsItem::Height + BTGraphicsItem::Height ) ),
									 BTGraphicsItem::Width,
									 BTGraphicsItem::Height } );
			g_node->SetNode( node );
			addItem( g_node );
			_Nodes.insert( node->GetHandle(), g_node );

			return g_node;
		}
	}
	else if( auto dec_node = DP_CAST<XE::DecoratorNode>( node ) )
	{
		if( dec_node->GetChild() )
		{
			if( auto dec_child = GetBehaviorTree()->GetNode( dec_node->GetChild() ) )
			{
				auto child = AddNode( dec_child, floor + 1, x );

				auto g_node = new BTGraphicsItem();
				g_node->setBoundingRect( {
					qreal( child->boundingRect().left() ),
					qreal( floor * ( BTGraphicsItem::Height + BTGraphicsItem::Height ) ),
									 BTGraphicsItem::Width,
									 BTGraphicsItem::Height } );
				g_node->SetNode( node );
				addItem( g_node );
				_Nodes.insert( node->GetHandle(), g_node );

				return g_node;
			}
		}
	}
	else if( auto dec_node = DP_CAST<XE::ConditionNode>( node ) )
	{
		if( dec_node->GetChild() )
		{
			if( auto dec_child = GetBehaviorTree()->GetNode( dec_node->GetChild() ) )
			{
				auto child = AddNode( dec_child, floor + 1, x );

				auto g_node = new BTGraphicsItem();
				g_node->setBoundingRect( {
					qreal( child->boundingRect().left() ),
					qreal( floor * ( BTGraphicsItem::Height + BTGraphicsItem::Height ) ),
									 BTGraphicsItem::Width,
									 BTGraphicsItem::Height } );
				g_node->SetNode( node );
				addItem( g_node );
				_Nodes.insert( node->GetHandle(), g_node );

				return g_node;
			}
		}
	}

	auto g_node = new BTGraphicsItem();
	g_node->setBoundingRect( { 
		qreal( x ), 
		qreal( floor * ( BTGraphicsItem::Height + BTGraphicsItem::Height ) ),
									 BTGraphicsItem::Width,
									 BTGraphicsItem::Height } );
	g_node->SetNode( node );
	addItem( g_node );
	_Nodes.insert( node->GetHandle(), g_node );

	x += BTGraphicsItem::Width + BTGraphicsItem::Width;

	return g_node;
}

void BTGraphicsScene::AddSocket( const XE::NodePtr & node )
{
	if( node == nullptr )
	{
		return;
	}

	if( auto comp_node = DP_CAST<XE::CompositeNode>( node ) )
	{
		if( comp_node->GetChildren().empty() )
		{
			return;
		}

		for( auto handle : comp_node->GetChildren() )
		{
			auto socket = new BTGraphicsSocket();

			socket->SetLastItem( _Nodes[node->GetHandle()] );
			socket->SetNextItem( _Nodes[handle] );

			addItem( socket );

			AddSocket( GetBehaviorTree()->GetNode( handle ) );
		}
	}
	else if( auto dec_node = DP_CAST<XE::DecoratorNode>( node ) )
	{
		if( dec_node->GetChild() == XE::NodeHandle::Invalid )
		{
			return;
		}

		auto socket = new BTGraphicsSocket();

		socket->SetLastItem( _Nodes[node->GetHandle()] );
		socket->SetNextItem( _Nodes[dec_node->GetChild()] );

		addItem( socket );

		AddSocket( GetBehaviorTree()->GetNode( dec_node->GetChild() ) );
	}
	else if( auto dec_node = DP_CAST<XE::ConditionNode>( node ) )
	{
		if( dec_node->GetChild() == XE::NodeHandle::Invalid )
		{
			return;
		}

		auto socket = new BTGraphicsSocket();

		socket->SetLastItem( _Nodes[node->GetHandle()] );
		socket->SetNextItem( _Nodes[dec_node->GetChild()] );

		addItem( socket );

		AddSocket( GetBehaviorTree()->GetNode( dec_node->GetChild() ) );
	}
}

void BTGraphicsScene::AddNodeAction( QMenu * menu, const XE::IMetaClassPtr & cls )
{
	auto add_root = [this]( XE::IMetaClassPtr val )
	{
		if( auto tree = GetBehaviorTree() )
		{
			auto handle = tree->AddNode( val );
			tree->SetRoot( handle );
			ResetGraphics();
		}
	};

	auto del_root = [this]()
	{
		if( auto tree = GetBehaviorTree() )
		{
			tree->RemoveNode( tree->GetRoot() );
			tree->SetRoot( XE::NodeHandle::Invalid );
			ResetGraphics();
		}
	};

	if( cls->GetDerivedClassSize() )
	{
		cls->VisitDerivedClass( [&]( XE::IMetaClassPtr val )
								{
									if( val->IsAbstract() && val->GetDerivedClassSize() )
									{
										auto m = menu->addMenu( QString::fromUtf8( val->GetName().ToCString() ) );
										AddNodeAction( m, val );
									}
									else if( val->IsAbstract() == false && val->GetDerivedClassSize() )
									{
										auto m = menu->addMenu( QString::fromUtf8( val->GetName().ToCString() ) );

										connect( m->menuAction(), &QAction::triggered, [this, val, add_root, del_root]()
												 {
													 GetDockWidget()->Execute( XE::MakeShared<PackDockCmd>( std::bind( add_root, val ), del_root ) );
												 } );

										AddNodeAction( m, val );
									}
									else if( val->IsAbstract() == false )
									{
										auto action = menu->addAction( QString::fromUtf8( val->GetName().ToCString() ) );
										connect( action, &QAction::triggered, [this, val, add_root, del_root]()
												 {
													 GetDockWidget()->Execute( XE::MakeShared<PackDockCmd>( std::bind( add_root, val ), del_root ) );
												 } );
									}
								} );
	}
}
