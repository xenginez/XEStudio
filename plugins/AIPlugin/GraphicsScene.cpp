#include "GraphicsScene.h"

#include "GraphicsView.h"

GraphicsScene::GraphicsScene( QObject * parent /*= nullptr */ )
	:QGraphicsScene( parent )
{
	setBackgroundBrush( QColor( "#393939" ) );
}

GraphicsScene::~GraphicsScene()
{

}

AIDockWidget * GraphicsScene::GetDockWidget() const
{
	return GetGraphicsView()->GetDockWidget();
}

GraphicsView * GraphicsScene::GetGraphicsView() const
{
	return _View;
}

void GraphicsScene::SetGraphicsView( GraphicsView * val )
{
	_View = val;
}

void GraphicsScene::drawBackground( QPainter * painter, const QRectF & rect )
{
	QGraphicsScene::drawBackground( painter, rect );

	painter->save();

	const int gridsize = 20;
	auto left = static_cast< int >( std::floor( rect.left() ) );
	auto right = static_cast< int >( std::ceil( rect.right() ) );
	auto top = static_cast< int >( std::floor( rect.top() ) );
	auto bottom = static_cast< int >( std::ceil( rect.bottom() ) );

	const auto first_left = left - ( left % gridsize );
	const auto first_top = top - ( top % gridsize );

	QVector<QLine> lines_light;
	QVector<QLine> lines_dark;
	for( auto x = first_left; x <= right; x += gridsize )
	{
		if( x % 100 != 0 )
			lines_light.push_back( QLine( x, top, x, bottom ) );
		else
			lines_dark.push_back( QLine( x, top, x, bottom ) );
	}
	for( auto y = first_top; y <= bottom; y += gridsize )
	{
		if( y % 100 != 0 )
			lines_light.push_back( QLine( left, y, right, y ) );
		else
			lines_dark.push_back( QLine( left, y, right, y ) );
	}

	painter->setPen( QColor( "#2F2F2F" ) );
	painter->drawLines( lines_light.data(), lines_light.size() );

	painter->setPen( QColor( "#292929" ) );
	painter->drawLines( lines_dark.data(), lines_dark.size() );

	painter->restore();
}
