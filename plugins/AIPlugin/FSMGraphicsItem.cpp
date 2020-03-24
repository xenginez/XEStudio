#include "FSMGraphicsItem.h"

#include "GraphicsView.h"
#include "GraphicsScene.h"
#include "GraphicsWidget.h"
#include "FSMGraphicsScene.h"

FSMGraphicsItem::FSMGraphicsItem( QGraphicsItem * parent /*= nullptr */ )
	:GraphicsItem( parent )
{
	setFlags( flags() | QGraphicsItem::ItemIsMovable | QGraphicsItem::ItemSendsGeometryChanges );
}

FSMGraphicsItem::~FSMGraphicsItem()
{

}

const XE::StatePtr & FSMGraphicsItem::GetState() const
{
	return _State;
}

void FSMGraphicsItem::SetState( const XE::StatePtr & val )
{
	_State = val;
	setPos( QPointF( val->GetPosition().x, val->GetPosition().y ) );
	setToolTip( QString::fromUtf8( val->GetName().ToCString() ) );
}

void FSMGraphicsItem::paint( QPainter * painter, const QStyleOptionGraphicsItem * option, QWidget * widget /* = nullptr */ )
{
	QPainterPath path;
	QRectF rect = { 0, 0, Radius * 2, Radius * 2 };

	QLinearGradient gradient( rect.topLeft(), rect.bottomRight() );
	gradient.setColorAt( 0.0f, Qt::gray );
	gradient.setColorAt( 1.0f, Qt::darkGray );

	if( _State->GetStateMachine()->GetRoot() == _State->GetHandle() )
	{
		gradient.setColorAt( 0.0f, Qt::green );
		gradient.setColorAt( 1.0f, Qt::darkGreen );
	}

	if( isSelected() )
	{
		gradient.setColorAt( 0.0f, Qt::red );
		gradient.setColorAt( 1.0f, Qt::darkRed );
	}

	path.addEllipse( rect );

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
	painter->drawText( rect, Qt::AlignCenter, QString::fromUtf8( _State->GetName().ToCString() ) );

	painter->restore();
}

QRectF FSMGraphicsItem::boundingRect() const
{
	return { 0, 0, Radius * 2, Radius * 2 };
}

void FSMGraphicsItem::contextMenuEvent( QGraphicsSceneContextMenuEvent * event )
{
	QMenu menu;

	auto root_action = menu.addAction( QObject::tr( "set to root" ) );
	root_action->connect( root_action, &QAction::triggered, [this]()
						  {
							  _State->GetStateMachine()->SetRoot( _State->GetHandle() );
						  } );
	auto del_action = menu.addAction( QObject::tr( "delete state" ) );
	del_action->connect( del_action, &QAction::triggered, [this]()
					  {
						  if ( _State->GetStateMachine()->GetRoot() == _State->GetHandle() )
						  {
							  QMessageBox::warning( nullptr, "error", "root state cannot be deleted" );
						  }
						  else
						  {
							  _State->GetStateMachine()->RemoveState( _State->GetHandle() );
							  static_cast< FSMGraphicsScene * >( GetGraphicsScene() )->ResetGraphics();
						  }
					  } );
	auto cond_menu = menu.addMenu( QObject::tr( "add condition" ) );
	AddConditionalAction( cond_menu, XE::Condition::GetMetaClassStatic() );

	menu.exec( QCursor::pos() );
}

QVariant FSMGraphicsItem::itemChange( GraphicsItemChange change, const QVariant & value )
{
	if( change == QGraphicsItem::GraphicsItemChange::ItemPositionChange )
	{
		auto pos = value.toPointF();
		_State->SetPosition( XE::Vec2( pos.x(), pos.y() ) );
	}
	else if( change == QGraphicsItem::GraphicsItemChange::ItemSelectedChange )
	{
		if( value.toBool() )
		{
			GetGraphicsScene()->GetGraphicsView()->GetGraphicsWidget()->ShowProperty( _State );
		}
		else
		{
			GetGraphicsScene()->GetGraphicsView()->GetGraphicsWidget()->Save();
			GetGraphicsScene()->GetGraphicsView()->GetGraphicsWidget()->ShowProperty( nullptr );
		}
	}

	return QGraphicsItem::itemChange( change, value );
}

void FSMGraphicsItem::AddConditionalAction( QMenu * menu, const XE::IMetaClassPtr & val ) const
{
	if( val->GetDerivedClassSize() )
	{
		val->VisitDerivedClass( [&]( XE::IMetaClassPtr derived )
								{
									if( derived->IsAbstract() && derived->GetDerivedClassSize() )
									{
										auto m = menu->addMenu( QString::fromUtf8( derived->GetName().ToCString() ) );
										AddConditionalAction( m, derived );
									}
									if( !derived->IsAbstract() && derived->GetDerivedClassSize() )
									{
										auto m = menu->addMenu( QString::fromUtf8( derived->GetName().ToCString() ) );

										m->connect( m->menuAction(), &QAction::triggered, [this, derived]()
														 {
															 static_cast< FSMGraphicsScene * >( GetGraphicsScene() )->AddCondition( _State->GetHandle(), derived );
														 } );

										AddConditionalAction( m, derived );
									}
									else if( !derived->IsAbstract() )
									{
										auto action = menu->addAction( QString::fromUtf8( derived->GetName().ToCString() ) );
										action->connect( action, &QAction::triggered, [this, derived]()
														 {
															 static_cast< FSMGraphicsScene * >( GetGraphicsScene() )->AddCondition( _State->GetHandle(), derived );
														 } );
									}
								} );
	}
}
