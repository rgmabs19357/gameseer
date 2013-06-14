#include "WallWnd.h"
#include "ui_WallWnd.h"
#include <QtDeclarative/QDeclarativeView>
#include <qdebug.h>
#include <sstream>
#include "QboxNet.h"
#include "screen.h"
#include "boost/foreach.hpp"

#include <Screen.h>
#include <wnd.h>
#include <Ring.h>
#include <QMessageBox>

void ScreenRectItem::paint(QPainter *painter,const QStyleOptionGraphicsItem *option,QWidget *widget)  {  
	uint32_t cc = ScreenMgr::instance()->getColCount();
	uint32_t rc = ScreenMgr::instance()->getRowCount();
	if ( !cc || !rc ) {return;}
	WallScene* scene = (WallScene*)this->scene();
	QRectF r = scene->sceneRect();
	double screenh  = r.height()/rc;
	double screenw  = r.width()/cc;

	painter->setBrush( Qt::black);
	for ( uint32_t i = 0; i < rc; ++i){
		QPointF start, end;
		start.setX( 0);
		start.setY( screenh*i);
		end.setX(r.width());
		end.setY( screenh*i);
		painter->drawLine(start, end);
	}

	for ( uint32_t i = 0; i < cc; ++i){
		QPointF start, end;
		start.setX( screenw*i);
		start.setY( 0);
		end.setX(screenw*i);
		end.setY(r.height() );
		painter->drawLine(start, end);
	}

	std::vector<QRectF> & rects = scene->getGreenRects();
	painter->setBrush( Qt::green);
	painter->setPen(QPen(Qt::black, 1));

	for (size_t i =0; i < rects.size(); ++i){
		painter->drawRect(rects[i]);
	}
}
//=======================================================================================================================================================================
ResizeItem::ResizeItem(Direction dir):
dir_(dir)
{
	setFlags(QGraphicsItem::ItemIsSelectable|QGraphicsItem::ItemClipsToShape|ItemSendsScenePositionChanges );
	switch(dir_){
		case Direction::LeftUp:
		case Direction::RightBottom:
			setCursor( Qt::SizeFDiagCursor);
			break;
		case Direction::LeftBottom:
		case Direction::RightUp:
			setCursor( Qt::SizeBDiagCursor);
			break;
	}
}

void ResizeItem::paint(QPainter *painter,const QStyleOptionGraphicsItem *option,QWidget *widget){
	static int size = 2;
	QRectF r;
	switch(dir_){
		case Direction::LeftUp:
			r= QRectF(0,0,size,size); break; 
		case Direction::RightBottom:
			r= QRectF(	((QGraphicsRectItem*)parentItem ())->rect().width()-size,((QGraphicsRectItem*)parentItem ())->rect().height()-size,size,size);   break;
		case Direction::LeftBottom:
			r= QRectF(	0,((QGraphicsRectItem*)parentItem ())->rect().height()-size,size,size);   break;
		case Direction::RightUp:
			r= QRectF(	((QGraphicsRectItem*)parentItem ())->rect().width()-size,0,size,size);   break;
	}

	setRect(r);
	painter->setBrush(QBrush(Qt::yellow));
	painter->drawRect(r);  
}
void ResizeItem::mouseDoubleClickEvent ( QGraphicsSceneMouseEvent * event ){
	WndRectItem* item= (WndRectItem*)parentItem();
	WallScene* wallscene = (WallScene*)this->scene();
	QRectF itemrect = item->rect();
	itemrect.translate(item->pos());

	QRectF greenRect = wallscene->getBigGreenRect(itemrect);
	uint32_t cc = ScreenMgr::instance()->getColCount();
	uint32_t rc = ScreenMgr::instance()->getRowCount();
	if ( !cc || !rc ) {return ;}

	QRectF r = wallscene->sceneRect();
	double screenh  = (r.height()/rc);
	double screenw  = (r.width()/cc);
	double x = itemrect.x();
	double y = itemrect.y();

	size_t countright = (int)((x+itemrect.width())/screenw);
	size_t countbottom = (int)((y+itemrect.height())/screenh);

	double offsetright = (x+itemrect.width())/screenw - countright;
	double offsetbottom = (y+itemrect.height())/screenh - countbottom;
	QPointF newPos = item->pos();
	QRectF newRect ;
	if (offsetright > 0){
		++countright;
	}else{
		newRect = QRect( newPos.x(), newPos.y(), (countright+1)*screenw-newPos.x(), (countbottom)*screenh-newPos.y());
		if ( greenRect.contains( newRect)){
			++countright;
		}
	}
	if (offsetbottom > 0){
		++countbottom;
	}else{
		newRect = QRect( newPos.x(), newPos.y(), (countright)*screenw-newPos.x(), (countbottom+1)*screenh-newPos.y());
		if ( greenRect.contains( newRect)){
			++countbottom;
		}
	}
	switch ( dir_){
		case Direction::RightBottom:
			newRect.setX(0);
			newRect.setY(0);
			newRect.setWidth(countright*screenw - newPos.x());
			newRect.setHeight(countbottom*screenh - newPos.y());
			break;
	}
	item->setPos(  newPos  );
	item->setRect(newRect);
	item->bringFront();
	item->wnd_->resizeWnd( newPos.x()/scene()->sceneRect().width(), newPos.y()/scene()->sceneRect().height(), newRect.width()/scene()->sceneRect().width(), newRect.height()/scene()->sceneRect().height());

}
void ResizeItem::resize( QPointF &curr){
	
	WndRectItem* item= (WndRectItem*)parentItem();
	WallScene* wallscene = (WallScene*)this->scene();

	QPointF curPos = curr;
	QPointF leftup =  item->pos();
	QPointF rightbottom =   QPointF( item->pos().x()+item->rect().width(), item->pos().y()+item->rect().height());
	QPointF rightup =   QPointF( item->pos().x()+item->rect().width(), item->pos().y()) ;
	QPointF leftbottom =  QPointF( item->pos().x(), item->pos().y()+item->rect().height()) ;
	QRectF itemrect = item->rect();
	itemrect.translate(item->pos());
	QRectF greenRect = wallscene->getBigGreenRect(itemrect);

	QPointF newPos;
	QRectF newRect;
	QRectF oldRect;
	switch ( dir_){
		//case Direction::LeftUp:
		//	newPos = curPos;
		//	if ( rightbottom.x() - curPos.x() < 50){
		//		newPos.setX(rightbottom.x()-50);
		//	}
		//	else if (  curPos.x() < greenRect.x()){
		//		newPos.setX(greenRect.x());
		//	}
		//	if ( rightbottom.y() - curPos.y() < 50){
		//		newPos.setY(rightbottom.y()-50);
		//	}
		//	else if ( curPos.y() < greenRect.y()){
		//		newPos.setY(greenRect.y());
		//	}

		//	newRect.setWidth(rightbottom.x() -newPos.x());
		//	newRect.setHeight(rightbottom.y() -newPos.y());
		//	
		//	break;
		case Direction::RightBottom:
			newPos= item->pos();
			newRect = QRectF( 0, 0, curPos.x()-leftup.x(), curPos.y()-leftup.y());
			if ( curPos.x() - leftup.x() < 50){
				newRect.setWidth(50);
			}
			else if (  curPos.x()  > greenRect.right()  ){
				newRect.setWidth(greenRect.right() - leftup.x());
			}
			if ( curPos.y() - leftup.y() < 50){
				newRect.setHeight(50);
			}
			else if (  curPos.y()  > greenRect.bottom() ){
				newRect.setHeight(greenRect.bottom() - leftup.y());
			}
			
			break;
		//case Direction::LeftBottom:
		//	newPos = QPointF(curPos.x(), leftup.y());
		//	if ( rightbottom.x() - curPos.x() < 50 ){
		//		newPos.setX(rightbottom.x() - 50);
		//	}else if (curPos.x() < 0 ){
		//		newPos.setX(0);
		//	}

		//	newRect = QRectF( 0, 0, rightbottom.x() - newPos.x(), curPos.y()-newPos.y());
		//	if ( newRect.height() < 50){
		//		newRect.setHeight(50);
		//	}else if (newRect.height()+newPos.y() > scene()->sceneRect().height()){
		//		newRect.setHeight(scene()->sceneRect().height() -newPos.y());
		//	}

		//	item->setPos(newPos);
		//	item->setRect(newRect);
		//	break;
		//case Direction::RightUp:
		//	newPos = QPointF(leftup.x(), curPos.y());
		//	if ( rightbottom.y() - newPos.y() < 50 ){
		//		newPos.setY(rightbottom.y() - 50);
		//	}else if (newPos.y() < 0 ){
		//		newPos.setY(0);
		//	}

		//	newRect = QRectF( 0, 0, curPos.x() - leftup.x(), rightbottom.y()-newPos.y());
		//	if ( newRect.width() < 50){
		//		newRect.setWidth(50);
		//	}else if (newRect.width()+newPos.x()> scene()->sceneRect().width()){
		//		newRect.setWidth(scene()->sceneRect().width() -newPos.x());
		//	}

		//	item->setPos(newPos);
		//	item->setRect(newRect);
		//	break;
	}
	item->setPos(  newPos  );
	item->setRect(newRect);
	item->bringFront();
	//item->wnd_->resizeWnd( newPos.x()/scene()->sceneRect().width(), newPos.y()/scene()->sceneRect().height(), newRect.width()/scene()->sceneRect().width(), newRect.height()/scene()->sceneRect().height());

}
void ResizeItem::mouseMoveEvent ( QGraphicsSceneMouseEvent * event ){
	QGraphicsRectItem::mouseMoveEvent(event);
	WndRectItem* parent = ((WndRectItem*)parentItem());
	if ( isResizing_) resize(event->scenePos());
}
void ResizeItem::mousePressEvent(QGraphicsSceneMouseEvent *event){

	QGraphicsRectItem::mousePressEvent(event);
	WndRectItem* parent = ((WndRectItem*)parentItem());
	pressPos_ = event->pos();
	isResizing_ = true;
}
void ResizeItem::mouseReleaseEvent ( QGraphicsSceneMouseEvent * event ){
	QGraphicsRectItem::mouseReleaseEvent(event);
	
	if ( isResizing_) {
		WndRectItem* parent = ((WndRectItem*)parentItem());
		WallScene* wallscene = (WallScene*)this->scene();
		parent->wnd_->resizeWnd( parent->pos().x()/wallscene->sceneRect().width()
			,parent->pos().y()/wallscene->sceneRect().height()
			,parent->rect().width()/wallscene->sceneRect().width()
			,parent->rect().height()/wallscene->sceneRect().height()
			);
	}
}
//=======================================================================================================================================================================
CloseItem::CloseItem(){
	isPressed_ = false;
	setFlags(QGraphicsItem::ItemIsSelectable|QGraphicsItem::ItemClipsToShape );
	setCursor( Qt::PointingHandCursor);
}
//QRectF CloseItem::boundingRect() const  {  return ;} 
void CloseItem::paint(QPainter *painter,const QStyleOptionGraphicsItem *option,QWidget *widget)  {  

	QRectF r = QRectF( ((QGraphicsRectItem*)parentItem())->rect().width() - 20, 0, 10, 10);
	setRect(r);
	painter->setBrush(QBrush(Qt::yellow));
	painter->drawRect(r);
	painter->drawLine(QPointF(r.x(), r.y()), QPointF(r.x()+r.width(), r.y()+r.height()));
	painter->drawLine(QPointF(r.x()+r.width(), r.y()), QPointF(r.x(), r.y()+r.height()));
	
	QGraphicsRectItem::paint(painter, option, widget);
} 
void CloseItem::mousePressEvent(QGraphicsSceneMouseEvent *event){
	isPressed_ = true;
	QGraphicsRectItem::mousePressEvent(event);
}
void CloseItem::mouseReleaseEvent ( QGraphicsSceneMouseEvent * event ){
	QGraphicsRectItem::mouseReleaseEvent(event);
	if (isPressed_){
		WndRectItem* item = (WndRectItem*)parentItem();
		WallScene *scene = ((WallScene*)item->scene());
		scene->removeItem(item);
		scene->wndItems_.erase(std::find( scene->wndItems_.begin(), scene->wndItems_.end(), item));
		WndMgr::instance()->closeWnd( item->wnd_);
		delete item;
	}
}
//=======================================================================================================================================================================
WndRectItem::WndRectItem(double x, double y, double w, double h, WallScene* wallscene, Wnd* wnd){
	setFlags(QGraphicsItem::ItemIsMovable |QGraphicsItem::ItemIsSelectable|QGraphicsItem::ItemClipsToShape|ItemSendsScenePositionChanges );
	//ResizeItem *item = new ResizeItem( ResizeItem::RightUp);
	ResizeItem *item1 = new ResizeItem( ResizeItem::RightBottom);
	//ResizeItem *item2 = new ResizeItem( ResizeItem::LeftBottom);
	//ResizeItem *item3 = new ResizeItem( ResizeItem::LeftUp);
	//MoveItem *item4 = new MoveItem( );
	CloseItem *item5 = new CloseItem( );
	//item->setParentItem(this);
	item1->setParentItem(this);
	//item2->setParentItem(this);
	//item3->setParentItem(this);
	//item4->setParentItem(this);
	item5->setParentItem(this);

	setCursor( Qt::OpenHandCursor);
	//setCursor( Qt::CrossCursor);
	isMoving_ = false;
	wallscene->addItem( this);
	setX(x);
	setY(y);
	setRect( QRectF(0, 0, w, h));
	if ( !wnd){
		wnd_ = WndMgr::instance()->createWnd( x/scene()->sceneRect().width(), y/scene()->sceneRect().height(), w/scene()->sceneRect().width(), h/scene()->sceneRect().height());
	}else wnd_ = wnd;
	setZValue( wnd_->getLayer());

}

WndRectItem::~WndRectItem(){
}
void WndRectItem::paint(QPainter *painter,const QStyleOptionGraphicsItem *option,QWidget *widget)  {  
	painter->setBrush(QBrush(Qt::red));
	QRectF r= rect();
	areaRect_ = QRectF(r.x()+r.width()/5*1, r.y()+r.height()/5*1, r.width()/5*3, r.height()/5*3);
	painter->drawRect(r);  
	painter->setBrush(QBrush(Qt::green));
	painter->drawRect(areaRect_);  
	painter->drawText(r, QString::fromStdString(wnd_->id_), QTextOption(Qt::Alignment::enum_type::AlignHCenter|Qt::Alignment::enum_type::AlignVCenter));
	QGraphicsRectItem::paint(painter, option, widget);
}  
void WndRectItem::bringFront(){
	setZValue(wnd_->bringFront());
}

void WndRectItem::mousePressEvent(QGraphicsSceneMouseEvent *event){
	if (event->button() == Qt::MouseButton::LeftButton){
		isMoving_ = true;
		QGraphicsRectItem::mousePressEvent(event);
		bringFront();
		setCursor( Qt::ClosedHandCursor);
	}
}
void	WndRectItem::mouseReleaseEvent ( QGraphicsSceneMouseEvent * event ){
	QGraphicsRectItem::mouseReleaseEvent(event);
	setCursor( Qt::OpenHandCursor);
	if (isMoving_ ){
		WallScene* wallscene = (WallScene*)this->scene();
		isMoving_ = false;
		wnd_->moveWnd(pos().x()/wallscene->width(), pos().y()/wallscene->height());
	}
}
void	WndRectItem::mouseMoveEvent ( QGraphicsSceneMouseEvent * event ){
	if (isMoving_) {
		QGraphicsRectItem::mouseMoveEvent(event);
	}
}
void	WndRectItem::hoverMoveEvent ( QGraphicsSceneHoverEvent * event ){
	qDebug()<<"WndRectItem::hoverMoveEvent";
}


QVariant WndRectItem::itemChange(GraphicsItemChange change, const QVariant &value)
{

    if(scene() && (change == ItemPositionChange || change ==ItemMatrixChange ) )
    {
		WallScene* wallscene = (WallScene*)this->scene();
		QPointF newPos = value.toPointF();
		
		if ( rect().width() == 0 || rect().height() == 0 )return newPos;
		QRectF thisrect = QRectF(pos().x(), pos().y(),rect().width(), rect().height());
		QRectF bigRect = wallscene->getBigGreenRect(thisrect);
		bigRect.setRight(bigRect.right() - rect().right());
		bigRect.setBottom(bigRect.bottom() - rect().bottom());
		if(!bigRect.contains(newPos)){
			newPos.setX(qMin(bigRect.right(), qMax(newPos.x(), bigRect.left())));
			newPos.setY(qMin(bigRect.bottom(), qMax(newPos.y(), bigRect.top())));
			return newPos;
		}
		
    }
 
    return QGraphicsRectItem::itemChange(change, value);
}

//=======================================================================================================================================================================
WallScene::WallScene(){
	isCreatingWnd_ = false;
	currInput_ = 0;
}
void WallScene::mousePressEvent(QGraphicsSceneMouseEvent *event){
	pressPos_ = event->scenePos();
	QList<QGraphicsItem *>  list = items( pressPos_, Qt::ItemSelectionMode::IntersectsItemShape, Qt::SortOrder::AscendingOrder);
	if ( currInput_ == 0){
		QMessageBox::warning(0, "Wanning", "There is no input signal has been selected!");
		return;
	}

	if ( list.size() == 0){//Into create wnd mode
		isCreatingWnd_ = true;
	}
	//qDebug()<<list.size();
	QGraphicsScene::mousePressEvent(event);
}
void WallScene::mouseMoveEvent ( QGraphicsSceneMouseEvent * event ){
	QGraphicsScene::mouseMoveEvent(event);
}

void WallScene::mouseReleaseEvent ( QGraphicsSceneMouseEvent * event ){
	if ( isCreatingWnd_){
		createWnd(event->scenePos());
		isCreatingWnd_ = false;
	}
	QGraphicsScene::mouseReleaseEvent(event);
}

void WallScene::createWnd( QPointF & releasePos){
	size_t height = 50, width = 50;
	QPointF pos;
	if (releasePos.x() > pressPos_.x() && releasePos.y() > pressPos_.y()){
		width = releasePos.x() - pressPos_.x();
		height = releasePos.y()-pressPos_.y();
		pos = pressPos_;
	}else if (releasePos.x() < pressPos_.x() && releasePos.y() < pressPos_.y()){
		width = -releasePos.x() + pressPos_.x();
		height = -releasePos.y()+pressPos_.y();
		pos = releasePos;
	}else if (releasePos.x() > pressPos_.x() && releasePos.y() < pressPos_.y()){
		width = releasePos.x() - pressPos_.x();
		height = -releasePos.y()+pressPos_.y();
		pos = QPointF( pressPos_.x(), releasePos.y());
	}else if (releasePos.x() < pressPos_.x() && releasePos.y() > pressPos_.y()){
		width = -releasePos.x() + pressPos_.x();
		height = releasePos.y()-pressPos_.y();
		pos = QPointF( releasePos.x(),  pressPos_.y());
	}
	if ( width > 50 && height > 50){
		//if ( currRing_== NULL ){
		//	QMessageBox::warning(0, "Wanning", "There is no Ring has been selected!");
		//	return;
		//}
		//if ( currRing_->isActivate_){
		//	QMessageBox::warning(0, "Wanning", "The Ring is not yet been activated!");
		//	return;
		//}
		createWndInGreenRect(QRectF(pos.x(), pos.y(), width, height));
	}
}
QRectF WallScene::getBigGreenRect( QRectF rect){
	uint32_t cc = ScreenMgr::instance()->getColCount();
	uint32_t rc = ScreenMgr::instance()->getRowCount();
	if ( !cc || !rc ) {return this->sceneRect();}

	QRectF r = this->sceneRect();
	double screenh  = (r.height()/rc);
	double screenw  = (r.width()/cc);
	double x = rect.x();
	double y = rect.y();

	size_t countleft = (int)(x/screenw);
	size_t counttop = (int)(y/screenh);
	size_t countright = (int)((x+rect.width())/screenw);
	size_t countbottom = (int)((y+rect.height())/screenh);

	double offsetleft = (x/screenw) - countleft;
	double offsettop = (y/screenh) - counttop;
	double offsetright = (x+rect.width())/screenw - countright;
	double offsetbottom = (y+rect.height())/screenh - countbottom;

	QPointF rightbottom( (countright+1)*screenw,  (countbottom+1)*screenh);
	QPointF lefttop ( countleft*screenw, counttop*screenh);

	size_t colCount = (size_t)((rightbottom.x() - lefttop.x()) / screenw);
	size_t rowCount = (size_t)((rightbottom.y() - lefttop.y()) / screenh);
	size_t rectCount = colCount*rowCount;

	std::vector<QRectF> rects = getGreenRects();

	QRectF growingRect(lefttop.x(), lefttop.y(), screenw, screenh);
	bool isInGrowingRect = false;
	size_t ic= 1;
	size_t ir= 1;
	for ( ; ic <= colCount; ++ic){
		int count = 0;
		growingRect.setWidth( screenw * ic);
		growingRect.setHeight( screenh * ir);
		for ( size_t ig= 0;  ig<rects.size();++ig){
			if ( growingRect.contains(rects[ig])){
				++count;
			}
		}
		if ( count != ir*ic){
			--ic;
			break;;
		}else if (ic == colCount){
			break;
		}
	}
	for ( ; ir <= rowCount; ++ir){
		int count = 0;
		growingRect.setWidth( screenw * ic);
		growingRect.setHeight( screenh * ir);
		for ( size_t ig= 0;  ig<rects.size();++ig){
			if ( growingRect.contains(rects[ig])){
				++count;
			}
		}
		if ( count != ir*ic){
			--ir;
			break;
		}else if (ir == rowCount){
			break;
		}
	}
	growingRect.setWidth( screenw * ic);
	growingRect.setHeight( screenh * ir);
	//qDebug()<<rect;
	//qDebug()<<growingRect;
	return growingRect;// a big rect that can contains the win rect which organized by screen rects.
}

bool WallScene::isInGreenRect( QRectF &rect){
	uint32_t cc = ScreenMgr::instance()->getColCount();
	uint32_t rc = ScreenMgr::instance()->getRowCount();
	if ( !cc || !rc ) {return false;}

	QRectF r = this->sceneRect();
	double screenh  = r.height()/rc;
	double screenw  = r.width()/cc;

	size_t countleft = (int)(rect.x()/screenw);
	size_t counttop = (int)(rect.y()/screenh);
	size_t countright = (int)((rect.x()+rect.width())/screenw);
	size_t countbottom = (int)((rect.y()+rect.height())/screenh);

	double offsetleft = (rect.x()/screenw) - countleft;
	double offsettop = (rect.y()/screenh) - counttop;
	double offsetright = (rect.x()+rect.width()) - countright;
	double offsetbottom = (rect.y()+rect.height()) - countbottom;

	QPointF rightbottom( offsetright>0 ? (countright+1)*screenw:countright*screenw , offsetbottom>0 ? (countbottom+1)*screenh:countbottom*screenh);
	QPointF lefttop ( countleft*screenw, counttop*screenh);
	QRectF bigRect( lefttop, rightbottom);// a big rect that can contains the win rect which organized by screen rects.
	size_t colCount = (size_t)((rightbottom.x() - lefttop.x()) / screenw);
	size_t rowCount = (size_t)((rightbottom.y() - lefttop.y()) / screenh);
	size_t rectCount = colCount*rowCount;

	std::vector<QRectF> rects = getGreenRects();
	std::vector<QRectF> inRects ;
	for ( size_t i = 0; i <rects.size();++i){//calculate how many screen rect insight the bigRect.
		if (bigRect.contains( rects[i])){
			inRects.push_back( rects[i]);
		}
	}
	if ( inRects.size() < rectCount){
		//not enough screen to create this window! logically should be the same.
		return false;
	}
	return true;
}
void WallScene::createWndInGreenRect( QRectF &rect){
	if (isInGreenRect(rect))
		wndItems_.push_back(new WndRectItem(rect.x(), rect.y(),rect.width(), rect.height(), this));
}
std::vector<QRectF> WallScene::getGreenRects(){
	uint32_t cc = ScreenMgr::instance()->getColCount();
	uint32_t rc = ScreenMgr::instance()->getRowCount();
	std::vector<QRectF> rects;
	if ( !cc || !rc ) {return rects;}

	QRectF r = this->sceneRect();
	double screenh  = r.height()/rc;
	double screenw  = r.width()/cc;
	QRectF screenRect = QRectF( 0, 0, screenw, screenh);

	Ring* ring = RingMgr::instance()->getRing(this->currRingid_.toStdString());
	if (ring && ring->isActivate()){ //draw rect for each rnode in activated ring
		std::vector<ResourceID> nodes = ring->getRnodes();
		size_t i = 0;
		if (nodes.size() >2  && GetRow(nodes.front()) == GetRow(nodes.back()) && GetCol(nodes.front()) == GetCol(nodes.back())){
			i = 1;
		}
		for ( ; i < nodes.size(); ++i){
			uint32_t row = GetRow(nodes[i]);
			uint32_t col = GetCol(nodes[i]);
			rects.push_back(QRectF((col -1) *screenw, (row -1) *screenh, screenw, screenh));
			
		}
	}else if (currInput_){//draw rect for chn
		uint32_t row = GetRow(currInput_);
		uint32_t col = GetCol(currInput_);
		rects.push_back(QRectF ((col -1) *screenw, (row -1) *screenh, screenRect.width(), screenRect.height()));
	}
	return rects;
}

//=======================================================================================================================================================================
WallWnd::WallWnd(QWidget* parent) :
    QWidget(parent)
	,ui(new Ui::WallWnd)
	,isResetting_(false)
{
    ui->setupUi(this);
	
	gv_ = findChild<QGraphicsView* >("wallView");

	scene_ = new WallScene;  
    scene_->setItemIndexMethod(QGraphicsScene::NoIndex);  

	screensItem_ = new ScreenRectItem;
	scene_->addItem(screensItem_);

	connect(scene_, SIGNAL(changed(const QList<QRectF>&)), this, SLOT(changed(const QList<QRectF> &)));
  
	gv_->setScene(scene_);
    gv_->setRenderHint(QPainter::Antialiasing);  
    gv_->setCacheMode(QGraphicsView::CacheBackground);  
    gv_->setViewportUpdateMode(QGraphicsView::FullViewportUpdate);  
	gv_->setDragMode(QGraphicsView::RubberBandDrag);  

	gv_->setBackgroundBrush(QBrush(Qt::lightGray));
	gv_->setInteractive(true);
    gv_->show();  

	cbRings_ = findChild<QComboBox* >("cbRing");
	cbChns_ = findChild<QComboBox* >("cbChn");
	cbWnds_ = findChild<QComboBox* >("cbWnd");
	connect(cbChns_, SIGNAL(activated(const QString &)), this, SLOT(currentChnIndexChanged (const QString &)) );

	connect(parent, SIGNAL(currentChanged(int)), this, SLOT(currentTabChanged (int)) );

	QPushButton* pbClose = findChild<QPushButton* >("pbCloseWnd");
	if (pbClose){
		connect(pbClose, SIGNAL(clicked()), this, SLOT(clickedCloseWnd()) );
	}
	QPushButton* pbActivateRing = findChild<QPushButton* >("pbActivateRing");
	if (pbActivateRing){
		connect(pbActivateRing, SIGNAL(clicked()), this, SLOT(clickedActivateRing()) );
	}
}
void WallWnd::changed ( const QList<QRectF> & region ){
	//for ( size_t i = 0; i < region.size(); i ++){
	//	qDebug()<<region[i];
	//}
	resetComboBoxes();
}
void WallWnd::clickedCloseWnd(){
	int index = cbWnds_->currentIndex();
	std::vector<Wnd*> wnds = WndMgr::instance()->getWnds();
	if ( index >= 0 && wnds.size()){
		for ( auto i = scene_->wndItems_.begin() ; i < scene_->wndItems_.end(); ){
			if ( wnds[index] == (*i)->wnd_){
				WndMgr::instance()->closeWnd((*i)->wnd_);
				(*i)->wnd_ = NULL;
				scene_->removeItem(*i);
				delete *i;
				i = scene_->wndItems_.erase(i);
			}else ++i;
		}
	}
}
void WallWnd::clickedActivateRing(){
	if ( !scene_->currRingid_.isEmpty() ){
		QPushButton* pb = (QPushButton*) sender();
		
		Ring * ring = RingMgr::instance()->getRing(scene_->currRingid_.toStdString());
		if ( ring->isActivate()){
			pb->setStyleSheet("");
			ring->activate(false);
		}else{
			pb->setStyleSheet("{color:red��background:yellow}");
			ring->activate(true);
		}
		screensItem_->update();
	}
}

WallWnd::~WallWnd(){
    delete ui;
}
void WallWnd::resetWnds(){
	std::vector<Wnd*> wnds = WndMgr::instance()->getWnds();
	screensItem_->update();
	for ( size_t i = 0 ; i < scene_->wndItems_.size(); ++i){
		scene_->removeItem(scene_->wndItems_[i]);
		delete scene_->wndItems_[i];
	}
	scene_->wndItems_.clear();
	for ( size_t i = 0; i < wnds.size();++i){
		double x = scene_->width()*wnds[i]->xPercent_;
		double y = scene_->height()*wnds[i]->yPercent_;
		double w = scene_->width()*wnds[i]->wPercent_;
		double h =  scene_->height()*wnds[i]->hPercent_;
		scene_->wndItems_.push_back( new WndRectItem(x, y, w, h, scene_, wnds[i]));
	}
}
void WallWnd::resetComboBoxes(){
	cbWnds_->setEnabled(false);
	cbRings_->setEnabled(false);
	cbChns_->setEnabled(false);

	std::vector<Ring*> rings = RingMgr::instance()->getRings();
	cbRings_->clear();
	for ( size_t i = 0; i < rings.size();++i){
		if ( rings[i]->size() >=2){
			cbRings_->addItem( QString::fromStdString(rings[i]->id_));
			if ( scene_->currRingid_.toStdString() == rings[i]->id_){//only the one currently referred, set to current index.
				cbRings_->setCurrentIndex( cbRings_->count()-1);
			}
		}
	}
	//the the top to be current
	if ( scene_->currRingid_.isEmpty() && cbRings_->count() )scene_->currRingid_ = cbRings_->currentText();

	std::vector<Wnd*> wnds = WndMgr::instance()->getWnds();
	cbWnds_->clear();
	for ( size_t i = 0; i < wnds.size();++i){
		cbWnds_->addItem( QString::fromStdString(wnds[i]->id_));//add all wnd to combox
		if ( scene_->currWndid_.toStdString() == wnds[i]->id_){//only the one currently referred, set to current index.
			cbWnds_->setCurrentIndex( cbWnds_->count()-1);
		}
	}
	//the the top to be current
	if ( scene_->currWndid_.isEmpty() && cbWnds_->count() )scene_->currWndid_ = cbWnds_->currentText();

	cbChns_->clear();
	inputs_ = ScreenMgr::instance()->getAvailableInput();
	for ( size_t i = 0; i < inputs_.size();++i){
		std::vector<Ring*> rs = RingMgr::instance()->getInputCorrespondActivatedRing(inputs_[i]);
		if ( rs.size()==0){
			cbChns_->addItem( QString::fromStdString(ToInputStrID(inputs_[i])));
			if ( scene_->currInput_ == inputs_[i]){//only the one currently referred, set to current index.
				cbChns_->setCurrentIndex( cbChns_->count()-1);
			}
		}
	}
	//the the top to be current
	if ( inputs_.size() >0 && scene_->currInput_==0 )scene_->currInput_ = inputs_.front();
	cbWnds_->setEnabled(true);
	cbRings_->setEnabled(true);
	cbChns_->setEnabled(true);
}
void WallWnd::currentTabChanged ( int index ){
	QTabWidget* tab = (QTabWidget*)sender();
	if (tab->tabText(index) == "Wall"){
		resetComboBoxes();
		resetWnds();
	}
}

void WallWnd::drawScreens(){
	uint32_t col = ScreenMgr::instance()->getColCount();
	uint32_t row = ScreenMgr::instance()->getRowCount();
}

void WallWnd::currentChnIndexChanged ( const QString & text ){
	for ( size_t i = 0; i < inputs_.size();++i){
		if ( ToInputStrID(inputs_[i]) == text.toStdString()){
			scene_->currInput_ = inputs_[i];
			screensItem_->update();
			break;
		}
	}
}
void WallWnd::currentRingIndexChanged ( const QString & text ){
	scene_->currRingid_ = text;
	screensItem_->update();
}

