#include "BTGraphicsItem.h"

#include "AIDockWidget.h"
#include "GraphicsView.h"
#include "GraphicsScene.h"
#include "GraphicsWidget.h"
#include "BTGraphicsScene.h"

class AddNodeCmd : public XESDockCmd
{
public:
	AddNodeCmd( const XE::NodePtr & parent, const XE::IMetaClassPtr & type, BTGraphicsScene * scene )
		:_Parent( parent ), _Type( type ), _Scene( scene )
	{

	}

public:
	void Todo() override
	{
		if( auto p_node = DP_CAST<XE::CompositeNode>( _Parent ) )
		{
			_Handle = p_node->AddChild( _Type );
		}
		else if( auto p_node = DP_CAST<XE::ConditionNode>( _Parent ) )
		{
			if( p_node->GetChild() != XE::NodeHandle::Invalid )
			{
				QMessageBox::warning( nullptr, QObject::tr( "warning" ), QObject::tr( "the node can only have one child node!" ) );
				return;
			}
			_Handle = p_node->AddChild( _Type );
		}
		else if( auto p_node = DP_CAST<XE::DecoratorNode>( _Parent ) )
		{
			if( p_node->GetChild() != XE::NodeHandle::Invalid )
			{
				QMessageBox::warning( nullptr, QObject::tr( "warning" ), QObject::tr( "the node can only have one child node!" ) );
				return;
			}
			_Handle = p_node->AddChild( _Type );
		}

		_Scene->ResetGraphics();
	}

	void Undo() override
	{
		if( auto p_node = DP_CAST<XE::CompositeNode>( _Parent ) )
		{
			p_node->RemoveChild( _Handle );
		}
		else if( auto p_node = DP_CAST<XE::ConditionNode>( _Parent ) )
		{
			p_node->RemoveChild();
		}
		else if( auto p_node = DP_CAST<XE::DecoratorNode>( _Parent ) )
		{
			p_node->RemoveChild();
		}

		_Scene->ResetGraphics();
	}

private:
	XE::NodePtr _Parent;
	XE::NodeHandle _Handle;
	XE::IMetaClassPtr _Type;
	BTGraphicsScene * _Scene;
};

class DelNodeCmd : public XESDockCmd
{
public:
	DelNodeCmd( const XE::NodePtr & parent, const XE::NodeHandle & handle, BTGraphicsScene * scene )
		:_Parent( parent ), _Handle( handle ), _Scene( scene )
	{

	}

public:
	void Todo() override
	{
		_Type = _Parent->GetBehaviorTree()->GetNode( _Handle )->GetMetaClass();

		if( auto p_node = DP_CAST<XE::CompositeNode>( _Parent ) )
		{
			p_node->RemoveChild( _Handle );
		}
		else if( auto p_node = DP_CAST<XE::ConditionNode>( _Parent ) )
		{
			p_node->RemoveChild();
		}
		else if( auto p_node = DP_CAST<XE::DecoratorNode>( _Parent ) )
		{
			p_node->RemoveChild();
		}

		_Scene->ResetGraphics();
	}

	void Undo() override
	{
		if( auto p_node = DP_CAST<XE::CompositeNode>( _Parent ) )
		{
			_Handle = p_node->AddChild( _Type );
		}
		else if( auto p_node = DP_CAST<XE::ConditionNode>( _Parent ) )
		{
			if( p_node->GetChild() != XE::NodeHandle::Invalid )
			{
				QMessageBox::warning( nullptr, QObject::tr( "warning" ), QObject::tr( "the node can only have one child node!" ) );
				return;
			}
			_Handle = p_node->AddChild( _Type );
		}
		else if( auto p_node = DP_CAST<XE::DecoratorNode>( _Parent ) )
		{
			if( p_node->GetChild() != XE::NodeHandle::Invalid )
			{
				QMessageBox::warning( nullptr, QObject::tr( "warning" ), QObject::tr( "the node can only have one child node!" ) );
				return;
			}
			_Handle = p_node->AddChild( _Type );
		}

		_Scene->ResetGraphics();
	}

private:
	XE::NodePtr _Parent;
	XE::NodeHandle _Handle;
	XE::IMetaClassPtr _Type;
	BTGraphicsScene * _Scene;
};

BTGraphicsItem::BTGraphicsItem( QGraphicsItem * parent /*= nullptr */ )
	:GraphicsItem( parent )
{
	setFlags( flags() | QGraphicsItem::ItemIsMovable | QGraphicsItem::ItemSendsGeometryChanges );
}

BTGraphicsItem::~BTGraphicsItem()
{

}

const XE::NodePtr & BTGraphicsItem::GetNode() const
{
	return _Node;
}

void BTGraphicsItem::SetNode( const XE::NodePtr & val )
{
	_Node = val;
	setToolTip( QString::fromUtf8( val->GetName().ToCString() ) );
}

QRectF BTGraphicsItem::boundingRect() const
{
	return _Rect;
}

void BTGraphicsItem::setBoundingRect( const QRectF & val )
{
	_Rect = val;
}

void BTGraphicsItem::paint( QPainter * painter, const QStyleOptionGraphicsItem * option, QWidget * widget /* = nullptr */ )
{
	QPainterPath path;
	QRectF rect = boundingRect();

	QLinearGradient gradient( rect.topLeft(), rect.bottomRight() );

	if( _Node->GetMetaClass()->CanConvert( XE::ClassID<XE::ActionNode>::Get() ) )
	{
		gradient.setColorAt( 0.0f, Qt::gray );
		gradient.setColorAt( 1.0f, Qt::darkGray );
	}
	else if( _Node->GetMetaClass()->CanConvert( XE::ClassID<XE::CompositeNode>::Get() ) )
	{
		gradient.setColorAt( 0.0f, Qt::yellow );
		gradient.setColorAt( 1.0f, Qt::darkYellow );
	}
	else if( _Node->GetMetaClass()->CanConvert( XE::ClassID<XE::ConditionNode>::Get() ) )
	{
		gradient.setColorAt( 0.0f, Qt::green );
		gradient.setColorAt( 1.0f, Qt::darkGreen );
	}
	else if( _Node->GetMetaClass()->CanConvert( XE::ClassID<XE::DecoratorNode>::Get() ) )
	{
		gradient.setColorAt( 0.0f, Qt::blue );
		gradient.setColorAt( 1.0f, Qt::darkBlue );
	}

	if( isSelected() )
	{
		gradient.setColorAt( 0.0f, Qt::red );
		gradient.setColorAt( 1.0f, Qt::darkRed );
	}

	path.addRect( rect );

	QPen pen;

	pen.setColor( Qt::white );


	painter->save();

	painter->setPen( pen );
	painter->setBrush( gradient );
	painter->fillPath( path, Qt::white );
	painter->drawPath( path );

	painter->restore();


	QFont font;
	font.setBold( true );

	painter->save();

	painter->setPen( Qt::white );
	painter->setFont( font );
	painter->drawText( rect, Qt::AlignCenter, QString::fromUtf8( _Node->GetName().ToCString() ) );

	painter->restore();
}

void BTGraphicsItem::contextMenuEvent( QGraphicsSceneContextMenuEvent * event )
{
	QMenu menu;

	if( _Node->GetMetaClass()->CanConvert( XE::ClassID<XE::ActionNode>::Get() ) == false )
	{
		auto node_menu = menu.addMenu( QObject::tr( "nodes" ) );
		AddNodeAction( node_menu, XE::ClassID<XE::Node>::Get() );
	}

	auto delete_action = menu.addAction( QObject::tr( "delete" ) );
	delete_action->connect( delete_action, &QAction::triggered, [this]()
							{
								auto scene = static_cast< BTGraphicsScene * >( GetGraphicsScene() );
								if( scene )
								{
									scene->GetDockWidget()->Execute( XE::MakeShared<DelNodeCmd>( _Node->GetBehaviorTree()->GetNode( _Node->GetParent() ), _Node->GetHandle(), scene ) );
								}
							} );

	menu.exec( QCursor::pos() );
}

QVariant BTGraphicsItem::itemChange( GraphicsItemChange change, const QVariant & value )
{
	if( change == QGraphicsItem::GraphicsItemChange::ItemSelectedChange )
	{
		if( value.toBool() )
		{
			GetGraphicsScene()->GetGraphicsView()->GetGraphicsWidget()->ShowProperty( _Node );
		}
		else
		{
			GetGraphicsScene()->GetGraphicsView()->GetGraphicsWidget()->Save();
			GetGraphicsScene()->GetGraphicsView()->GetGraphicsWidget()->ShowProperty( nullptr );
		}
	}
	else if( change == QGraphicsItem::GraphicsItemChange::ItemPositionChange )
	{
		return QPointF( 0, 0 );
	}

	return GraphicsItem::itemChange( change, value );
}

void BTGraphicsItem::AddNodeAction( QMenu * menu, const XE::IMetaClassPtr & cls )
{
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

										m->connect( m->menuAction(), &QAction::triggered, [this, val]()
													{
														auto scene = static_cast< BTGraphicsScene * >( GetGraphicsScene() );
														if( scene )
														{
															scene->GetDockWidget()->Execute( XE::MakeShared<AddNodeCmd>( _Node, val, scene ) );
														}
													} );

										AddNodeAction( m, val );
									}
									else if( val->IsAbstract() == false )
									{
										auto action = menu->addAction( QString::fromUtf8( val->GetName().ToCString() ) );
										action->connect( action, &QAction::triggered, [this, val]()
														 {
															 auto scene = static_cast< BTGraphicsScene * >( GetGraphicsScene() );
															 if( scene )
															 {
																 scene->GetDockWidget()->Execute( XE::MakeShared<AddNodeCmd>( _Node, val, scene ) );
															 }
														 } );
									}
								} );
	}
}
