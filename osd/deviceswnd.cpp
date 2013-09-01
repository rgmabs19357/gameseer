#include "deviceswnd.h"
#include "ui_deviceswnd.h"
#include <QTableWidgetItem>
#include "configmgr.h"
#include <functional>
#include <qdebug>
#include <Windows.h>
#include <boost/foreach.hpp>
#include "TestQbox.h"
#include "ui_mainwindow.h"
#include <OsdImage.h>
#include <OsdProjMode.h>
#include <Ring.h>
#include <mode.h>
#include <QMessageBox>

#undef min
using namespace std::placeholders;




OsdWnd::OsdWnd(ResourceID screenid)
:QMainWindow(0)
,screenid_(screenid)
,ui(new Ui::MainWindow)
,osdImage_(new OsdImage(this, screenid))
,osdProjMode_(new OsdProjMode(this, screenid))
{
    ui->setupUi(this);
	_tab = findChild<QTabWidget*>( "tabWidget");
	_tab->addTab(osdImage_, "Image" );
	_tab->addTab(osdProjMode_, "Projection Mode" );
	//connect( _tab, SIGNAL(currentChanged (int)), this, SLOT(tabChanged(int)));
	

}


void OsdWnd::tabChanged (int ){
	//QWidget* currWidget = _tab->widget( index);
}
OsdWnd::~OsdWnd(){
    delete ui;
}
void ScreenConnBtn::conn(){
	Screen* scrn = ScreenMgr::instance()->getScreen(screenid_);
	if ( scrn){
		if ( scrn->setAddress( address_->text().toStdString())){
			scrn->connect();
			setText("Connecting...");
			this->setEnabled(false);
			address_->setEnabled(false);
			osdBtn_->setEnabled(false);
			testBtn_->setEnabled(false);
			dlpBtn_->setEnabled(true);
			dlpBtn_->setText("Unknow");
			scrn->versionRequest( std::bind( &ScreenConnBtn::connectedCallback, this, _1, _2), QboxDataMap() );
			scrn->getDlpRequest( std::bind( &ScreenConnBtn::dlpCallback, this, _1, _2) );
		}
	}
}
void ScreenConnBtn::disconn(){
	ScreenMgr::instance()->closeAllWnds();
	Screen* scrn = ScreenMgr::instance()->getScreen(screenid_);
	
	osdBtn_->setEnabled(false);
	testBtn_->setEnabled(false);
	address_->setEnabled(true);
	dlpBtn_->setEnabled(false);
	
	if (testQbox_ && !testQbox_->isHidden() ) testQbox_->hide();
	if (osdBtn_ && osdBtn_->isEnabled() ) osdBtn_->setEnabled(false);
	setText("Connect");
	Sleep(500);
	scrn->disconnect();
}
void ScreenConnBtn::clickit(){
	if ( address_->text().isEmpty() ){
		address_->setText("192.168.67.103") ;
	}
	if ( !address_->text().isEmpty() && text() == "Connect"){
		conn();
	}else if (text() == "Disconnect"){
		disconn();
	}
}
void ScreenConnBtn::clickOsd(){
	if (osdWnd_ == NULL){
		osdWnd_ = new OsdWnd(screenid_);
		osdWnd_->setWindowTitle(address_->text() );
		osdWnd_->resize( 800, 600);
		osdWnd_->show();
	}else{
		if (osdWnd_->isHidden()){
			osdWnd_->show();
		}
	}
}
void ScreenConnBtn::clickTest(){
	if (testQbox_ == NULL){
		testQbox_ = new TestQbox(screenid_);
		testQbox_->resize( 800, 600);
		testQbox_->show();
	}else{
		if (testQbox_->isHidden()){
			testQbox_->show();
		}
	}
}
bool ScreenConnBtn::tempdlpCallback( uint32_t , QboxDataMap data){
	if ( data["error"] != "0") return true;
	auto found = data.find("data");
	if (found != data.end()){
		std::string val = found->second;
		int val1 = val[0];
		int val2 = val[1];
		int val3 = val[2];
		int val4 = val[3];
		int val5 = val[4];
		int val6 = val[5];
		int val7 = val[6];
	}
	return true;
}
bool ScreenConnBtn::setdlpCallback( uint32_t , QboxDataMap data){
	if ( data["error"] != "0") return true;
	dlpBtn_->setEnabled(true);
	return true;
}
void ScreenConnBtn::clickDlp(){
	Screen* srn = ScreenMgr::instance()->getScreen( screenid_);
	if ( srn == NULL ) return;
	if ( dlpBtn_->text() == "Turn off"){
		dlpBtn_->setText("Turn on");
		dlpBtn_->setStyleSheet("");
		dlpBtn_->setEnabled(false);
		srn->setDlpRequest( 0,std::bind( &ScreenConnBtn::setdlpCallback, this, _1, _2) );
	}else if(dlpBtn_->text() == "Turn on") {
		dlpBtn_->setText("Turn off");
		dlpBtn_->setStyleSheet("* { background-color: lightGreen }");
		srn->setDlpRequest( 1,std::bind( &ScreenConnBtn::setdlpCallback, this, _1, _2) );
		dlpBtn_->setEnabled(false);
	}
}

bool ScreenConnBtn::dlpCallback( uint32_t , QboxDataMap data){
	if ( data["error"] != "0") return true;

	int power = data["ASIC"].at(0);
	int lamp = data["LAMP"].at(0);
	int fan = data["FAN"].at(0);
	if ( power == 1){
		dlpBtn_->setText("Turn off");
		dlpBtn_->setStyleSheet("* { background-color: lightGreen }");
		Screen* srn = ScreenMgr::instance()->getScreen( screenid_);

		std::string value;
		value.resize(7);
		value[0] = 0;
		value[1] = 0;
		value[2] = 0;
		value[3] = 0;
		value[4] = 0;
		value[5] = 0;
		value[6] = 0;
		QboxDataMap datamap;
		datamap["addr"] = QString::number( 0xB7).toStdString();
		datamap["len"] = QString::number(7).toStdString();
		datamap["value"] = value;
		srn->osdRequest( std::bind( &ScreenConnBtn::tempdlpCallback, this, _1, _2) , datamap );
		Sleep(1000);
		srn->osdRequestRead( 0xb7, 7, std::bind( &ScreenConnBtn::tempdlpCallback, this, _1, _2), 0x34);// for osd request
	}else{
		dlpBtn_->setText("Turn on");
		dlpBtn_->setStyleSheet("");
	}
	if ( fan == 1){
		//QMessageBox::warning(0, "Wanning", "Fan Error, DLP will be turn off!");
	}else{
	}
	return true;
}
bool ScreenConnBtn::connectedCallback( uint32_t , QboxDataMap){
	setText("Disconnect");
	this->setEnabled(true);
	osdBtn_->setEnabled(true);
	testBtn_->setEnabled(true);
	return true;
}

ScreenConnBtn::ScreenConnBtn( ResourceID screenid, const std::string & ip ):
	QPushButton()
	,osdWnd_(0)
	,testQbox_(0)
	,screenid_(screenid)
	,row_( new QTableWidgetItem)
	,col_(new QTableWidgetItem)
	,temp_(new QTableWidgetItem)
	,address_(new QLineEdit)
	,osdBtn_(new QPushButton)
	,testBtn_(new QPushButton)
	,dlpBtn_(new QPushButton)
{
	this->setText( "Connect");

	row_->setText( QString::number( GetRow(screenid)) );
	row_->setTextAlignment( Qt::AlignVCenter|Qt::AlignHCenter);
	row_->setFlags( Qt::ItemIsEnabled );

	col_->setText(QString::number( GetCol(screenid)));
	col_->setFlags( Qt::ItemIsEnabled );
	col_->setTextAlignment( Qt::AlignVCenter|Qt::AlignHCenter);

	temp_->setText( QString::number( GetRow(0)) );
	temp_->setTextAlignment( Qt::AlignVCenter|Qt::AlignHCenter);
	temp_->setFlags( Qt::ItemIsEnabled );

	osdBtn_->setEnabled(false);
	osdBtn_->setText( "OSD");
	connect( osdBtn_, SIGNAL(clicked()), this, SLOT(clickOsd()) );

	testBtn_->setEnabled(false);
	testBtn_->setText( "Test");
	connect( testBtn_, SIGNAL(clicked()), this, SLOT(clickTest()) );

	dlpBtn_->setEnabled(false);
	dlpBtn_->setText( "Unknow");
	connect( dlpBtn_, SIGNAL(clicked()), this, SLOT(clickDlp()) );

	QRegExp ipRx("((2[0-4]\\d|25[0-5]|[01]?\\d\\d?)\\.){3}(2[0-4]\\d|25[0-4]|[01]?\\d\\d?)");
	QRegExpValidator *pIpValidator = new QRegExpValidator(ipRx);
	address_->setValidator(pIpValidator);
	address_->setAlignment( Qt::AlignVCenter| Qt::AlignHCenter);
	address_->setText( QString::fromStdString( ip) );

	connect( this, SIGNAL(clicked()), this, SLOT(clickit()) );

	connect( address_, SIGNAL(editingFinished()), this, SLOT(addressEditFinished()) );
	
}

ScreenConnBtn::~ScreenConnBtn(){
	if (osdWnd_) delete osdWnd_;
	if (testQbox_) delete testQbox_;
}

void ScreenConnBtn::addressEditFinished(){
	Screen* srn = ScreenMgr::instance()->getScreen( screenid_);
	srn->setAddress( address_->text().toStdString());
}

DevicesWnd::DevicesWnd(QWidget *parent) :
    QWidget(parent)
    ,ui(new Ui::DevicesWnd)
{
    ui->setupUi(this);

    tableDevices_ = findChild<QTableWidget* >("tableDevices");
    tableDevices_->setColumnCount(9);

    QStringList sl;
	sl.push_back( "Row");
	sl.push_back( "Col");
	sl.push_back( "IP");
    sl.push_back( "OSD");
    sl.push_back( "Connection");
	sl.push_back( "Test");
    tableDevices_->setHorizontalHeaderLabels(sl );
	tableDevices_->setColumnWidth( 0, 35);
	tableDevices_->setColumnWidth( 1, 35);

    connect( tableDevices_, SIGNAL(itemClicked(QTableWidgetItem *)), this, SLOT(itemClicked(QTableWidgetItem *)));
    connect( tableDevices_, SIGNAL(cellChanged(int,int)), this, SLOT(cellChanged(int,int)));

    startTimer(500);
	QPushButton * clearWall = findChild<QPushButton* >("clearWall");
	connect( clearWall, SIGNAL( clicked()), this, SLOT(clearWall()) );
	QPushButton * incrCol = findChild<QPushButton* >("incrCol");
	connect( incrCol, SIGNAL( clicked()), this, SLOT(incrCol()) );
	QPushButton * incrRow = findChild<QPushButton* >("incrRow");
	connect( incrRow, SIGNAL( clicked()), this, SLOT(incrRow()) );
	QPushButton * decrCol = findChild<QPushButton* >("decrCol");
	connect( decrCol, SIGNAL( clicked()), this, SLOT(decrCol()) );
	QPushButton * decrRow = findChild<QPushButton* >("decrRow");
	connect( decrRow, SIGNAL( clicked()), this, SLOT(decrRow()) );

	QPushButton * connAll = findChild<QPushButton* >("connAll");
	connect( connAll, SIGNAL( clicked()), this, SLOT(connAll()) );
	QPushButton * disconnAll = findChild<QPushButton* >("disconnAll");
	connect( disconnAll, SIGNAL( clicked()), this, SLOT(disconnAll()) );

	initAddresses();

	QPushButton* setupTest = findChild<QPushButton* >("setupTest");
	if ( setupTest){
		setupTest->hide();
		connect( setupTest, SIGNAL(clicked()), this, SLOT(setupTestClick()));
	}

	QPushButton * pbLoad = findChild<QPushButton* >("pbLoad");
	connect( pbLoad, SIGNAL( clicked()), this, SLOT(clickedLoad()) );
	QPushButton * pbSave = findChild<QPushButton* >("pbSave");
	connect( pbSave, SIGNAL( clicked()), this, SLOT(clickedSave()) );
}
DevicesWnd::~DevicesWnd()
{
    delete ui;
}

void DevicesWnd::clickedLoad(){
	clearWall();
	QDomElement root = ConfigMgr::instance()->getDoc()->documentElement();
	QDomNodeList items = root.elementsByTagName("wall");
	
	if ( items.size() >0 ){
		QDomElement wallElm = items.at(0).toElement();
		size_t row = wallElm.attribute("row").toInt();
		size_t col = wallElm.attribute("col").toInt();
		for ( int i = 0; i <col;++i){
			ScreenMgr::instance()->addScreenCol();
		}
		for ( int i = 1; i <row;++i){
			ScreenMgr::instance()->addScreenRow();
		}
	}

	items = root.elementsByTagName("screen");
	for (size_t i = 0; i < items.size();++i){
		QDomElement elm = items.at(i).toElement();
		Screen* srn = ScreenMgr::instance()->getScreen( elm.attribute("id").toInt() );
		srn->setAddress(elm.attribute("ip").toStdString() );
		newAddress(srn->getResourceID(), srn->getAddress());
	}
	items = root.elementsByTagName("ring");
	for (size_t i = 0; i < items.size();++i){
		QDomElement ringelm = items.at(i).toElement();
		QString id = ringelm.attribute("id");
		Ring* ring = RingMgr::instance()->getRing(id.toStdString() );
		if ( ring == NULL){
			ring = RingMgr::instance()->createRing(id.toStdString() );
		}
		QDomElement rnode = ringelm.firstChildElement();
		while(rnode != QDomElement()){
			QString rnodeid = rnode.attribute("id");
			ring->makeNode( rnodeid.toInt() , ring->size());
			rnode = rnode.nextSibling().toElement();
		}
	}
	items = root.elementsByTagName("mode");
	ModeMgr::instance()->clear();
	for (size_t i = 0; i < items.size();++i){
		QDomElement modeelm = items.at(i).toElement();
		QString id = modeelm.attribute("id");
		Mode* mode= ModeMgr::instance()->createMode(id.toStdString() );

		QDomElement wnode = modeelm.firstChildElement();
		while(wnode != QDomElement()){
			
			WndData wd ;
			wd.wndid_ = wnode.attribute("wndid").toStdString();
			wd.ringid_ = wnode.attribute("ringid").toStdString();
			wd.inputid_ = wnode.attribute("inputid").toInt();
			wd.xPercent_ = wnode.attribute("x").toDouble();
			wd.yPercent_ = wnode.attribute("y").toDouble();
			wd.wPercent_ = wnode.attribute("w").toDouble();
			wd.hPercent_ = wnode.attribute("h").toDouble();
			wd.axPercent_ = wnode.attribute("ax").toDouble();
			wd.ayPercent_ = wnode.attribute("ay").toDouble();
			wd.awPercent_ = wnode.attribute("aw").toDouble();
			wd.ahPercent_ = wnode.attribute("ah").toDouble();
			mode->wnds_.push_back(wd);
			wnode = wnode.nextSibling().toElement();
		}
	}
}
void DevicesWnd::clickedSave(){
	QDomElement root = ConfigMgr::instance()->getDoc()->documentElement();

	size_t row = ScreenMgr::instance()->getRowCount();
	size_t col = ScreenMgr::instance()->getColCount();

	QDomNodeList items = root.elementsByTagName("wall");
	QDomElement wallElm;
	if ( items.size() >0 ){
		wallElm = items.at(0).toElement();
	}else{
		wallElm = ConfigMgr::instance()->getDoc()->createElement("wall");
		root.appendChild(wallElm);
	}
	wallElm.setAttribute("row", row);
	wallElm.setAttribute("col", col);

	items = root.elementsByTagName("screen");
	std::vector<Screen*> srns;
	for (size_t i =1; i <=row; ++i){
		for (size_t j =1; j <=col; ++j){
			srns.push_back( ScreenMgr::instance()->getScreen( ToScreenID(i, j)) );
		}
	}
	while (items.size()){
		root.removeChild(items.at(0));
	}
	for (size_t i =0; i <srns.size(); ++i){
		QDomElement elm = ConfigMgr::instance()->getDoc()->createElement("screen");
		Screen* srn = srns[i];
		elm.setAttribute("id", QString::number( srn->getResourceID()));
		elm.setAttribute("ip",QString::fromStdString( srn->getAddress()));
		root.appendChild(elm);
	}

	items = root.elementsByTagName("ring");
	while (items.size()){
		root.removeChild(items.at(0));
	}
	std::vector<Ring*> rings = RingMgr::instance()->getRings();
	for (size_t i =0; i <rings.size(); ++i){
		QDomElement ringelm = ConfigMgr::instance()->getDoc()->createElement("ring");
		ringelm.setAttribute("id", QString::fromStdString( rings[i]->id_));
		root.appendChild(ringelm);
		std::vector<ResourceID> rnodes = rings[i]->getRnodes();
		for ( size_t j = 0; j < rnodes.size();++j){
			QDomElement elm = ConfigMgr::instance()->getDoc()->createElement("rnode");
			elm.setAttribute("id", QString::number( rnodes[j]));
			ringelm.appendChild(elm);
		}
	}

	items = root.elementsByTagName("mode");
	while (items.size()){
		root.removeChild(items.at(0));
	}
	std::vector<Mode*> modes = ModeMgr::instance()->getAllModes();
	for (size_t i =0; i <modes.size(); ++i){
		QDomElement modeelm = ConfigMgr::instance()->getDoc()->createElement("mode");
		modeelm.setAttribute("id", QString::fromStdString( modes[i]->id_));
		root.appendChild(modeelm);

		for ( size_t j = 0; j < modes[i]->wnds_.size();++j){
			QDomElement elm = ConfigMgr::instance()->getDoc()->createElement("wnd");
			elm.setAttribute("wndid", QString::fromStdString( modes[i]->wnds_[j].wndid_));
			if (!modes[i]->wnds_[j].ringid_.empty() ){
				elm.setAttribute("ringid", QString::fromStdString( modes[i]->wnds_[j].ringid_));
			}
			elm.setAttribute("inputid", QString::number( modes[i]->wnds_[j].inputid_));
			elm.setAttribute("x", QString::number( modes[i]->wnds_[j].xPercent_));
			elm.setAttribute("y", QString::number( modes[i]->wnds_[j].yPercent_));
			elm.setAttribute("w", QString::number( modes[i]->wnds_[j].wPercent_));
			elm.setAttribute("h", QString::number( modes[i]->wnds_[j].hPercent_));
			elm.setAttribute("ax", QString::number( modes[i]->wnds_[j].axPercent_));
			elm.setAttribute("ay", QString::number( modes[i]->wnds_[j].ayPercent_));
			elm.setAttribute("aw", QString::number( modes[i]->wnds_[j].awPercent_));
			elm.setAttribute("ah", QString::number( modes[i]->wnds_[j].ahPercent_));
			modeelm.appendChild(elm);
		}
	}
	ConfigMgr::instance()->save();
}

void DevicesWnd::setupTestClick(){
	ScreenMgr::instance()->setupTest();
}

void DevicesWnd::incrCol(){
	auto ss = ScreenMgr::instance()->addScreenCol();
	BOOST_FOREACH( uint32_t srn, ss){
		newAddress( srn, std::string());
	}
	//saveWall();
}
void DevicesWnd::incrRow(){
	auto ss = ScreenMgr::instance()->addScreenRow();
	BOOST_FOREACH( uint32_t srn, ss){
		newAddress( srn, std::string());
	}
	//saveWall();
}
void DevicesWnd::clearWall(){
	auto ss = ScreenMgr::instance()->clearWall();
	BOOST_FOREACH( uint32_t srn, ss){
		deleteAddress( srn);
	}
	//saveWall();
}

void DevicesWnd::decrCol(){
	auto ss = ScreenMgr::instance()->removeScreenCol();
	BOOST_FOREACH( uint32_t srn, ss){
		deleteAddress( srn);
	}
	//saveWall();
}
void DevicesWnd::decrRow(){
	auto ss = ScreenMgr::instance()->removeScreenRow();
	BOOST_FOREACH( uint32_t srn, ss){
		deleteAddress( srn);
	}
	//saveWall();
}

void DevicesWnd::disconnAll(){
	for ( uint32_t i = 0; i < tableDevices_->rowCount(); ++i){
		ScreenConnBtn* t = (ScreenConnBtn*)tableDevices_->cellWidget( i, 4);
		if ( t->text() == "Disconnect"){
			t->disconn();
		}
	}
}
void DevicesWnd::connAll(){
	for ( uint32_t i = 0; i < tableDevices_->rowCount(); ++i){
		ScreenConnBtn* t = (ScreenConnBtn*)tableDevices_->cellWidget( i, 4);
		if ( t->text() == "Connect"){
			t->conn();
		}
	}
}

//load addresses from configuration
void DevicesWnd::initAddresses(){
    //if ( addresses_.size() > 0) return;
    //QDomElement address = ConfigMgr::instance()->getAddressElem().firstChildElement();
    //while (address != QDomElement() ){
    //    QString ip = address.attribute( "ip");
    //    if ( addresses_.find( ip) == addresses_.end() ){
    //        QboxAddress * aa = new QboxAddress(ip );
    //        newAddress(aa);
    //    }
    //    address = address.nextSiblingElement();
    //}
}

void DevicesWnd::newAddress( ResourceID screenid, const std::string &ip){

	ScreenConnBtn * connBtn = new ScreenConnBtn( screenid , ip );
	tableDevices_->setRowCount(tableDevices_->rowCount()+1);  
	tableDevices_->setItem ( tableDevices_->rowCount()-1, 0, connBtn->row_ );
	tableDevices_->setItem ( tableDevices_->rowCount()-1, 1, connBtn->col_ );
	
	tableDevices_->setCellWidget(tableDevices_->rowCount()-1, 2, connBtn->address_);
	tableDevices_->setCellWidget ( tableDevices_->rowCount()-1, 3, connBtn->osdBtn_ );
	tableDevices_->setCellWidget ( tableDevices_->rowCount()-1, 4, connBtn );
	tableDevices_->setCellWidget ( tableDevices_->rowCount()-1, 5, connBtn->testBtn_ );
	tableDevices_->setCellWidget ( tableDevices_->rowCount()-1, 6, connBtn->dlpBtn_ );
	tableDevices_->setItem ( tableDevices_->rowCount()-1, 7, connBtn->temp_ );
}
void DevicesWnd::deleteAddress( ResourceID screenid){
	uint32_t row = GetRow(screenid );
	uint32_t col = GetCol(screenid );

	for ( size_t i = 0; i < tableDevices_->rowCount() ; ++i){
		QTableWidgetItem * rowitem = tableDevices_->item( i, 0);
		QTableWidgetItem * colitem = tableDevices_->item( i, 1);
		if (rowitem->text().toUInt() ==row  && colitem->text().toUInt() == col){
			tableDevices_->removeRow( i);
			break;
		}
	}
}

void DevicesWnd::timerEvent ( QTimerEvent * event ){
	ScreenMgr::instance()->run();
}




void DevicesWnd::connectImpl( ){

}

void DevicesWnd::itemClicked(QTableWidgetItem * item)
{
    if (item->column() == 4 ){
        if(item->text() == "Connect" ){

        }
		if(item->text() == "Disconnect" ){

        }
    }
}

void DevicesWnd::cellChanged(int row,int col){
}

