#include "OIDDial.h"
#include "OIDInputDlg.h"
#include "ConfigMgr.h"
#include <QDebug>
#include <QEvent>
using namespace std::tr1::placeholders;


OIDDial::OIDDial( QWidget* w):
QDial(w)
,val_(0){
	connect( this, SIGNAL(valueChanged(int )), this, SLOT(fireSnmp(int )));
	startTimer(500);
	installEventFilter(this);
	setToolTip( objectName());

}

void OIDDial::initSnmp(){
	SnmpNet::instance()->addAsyncGet( objectName().toStdString().c_str(), ConfigMgr::instance()->getOid(objectName()).toStdString().c_str(), "public", std::bind<SnmpCallbackFunc>( &OIDDial::snmpCallback, this, _1, _2, _3, _4) );
}

bool OIDDial::eventFilter ( QObject * watched, QEvent * event ){
	if (ConfigMgr::instance()->isOidEditable() &&
		(event->type() == event->MouseButtonPress ||
		event->type() == event->MouseButtonRelease ||
		event->type() == event->MouseButtonDblClick ||
		event->type() == event->MouseMove ||
		event->type() == event->MouseTrackingChange||
		event->type() == event->Enter||
		event->type() == event->Leave
		)
		
		){
			if (event->type() == event->MouseButtonRelease){
				QString oid = OIDInputDlg::getNewOid( this->objectName());
				if (!oid.isEmpty()){
					SnmpNet::instance()->addAsyncGet(objectName().toStdString().c_str(),  oid.toStdString().c_str(), "public", std::bind<SnmpCallbackFunc>( &OIDDial::snmpCallback, this, _1, _2, _3, _4) );
				}
			}
			return true;
	}else{
		QDial::eventFilter(watched, event);
	}
    return false;
}

void	OIDDial::timerEvent ( QTimerEvent * e ){
	size_t now = GetTickCount();
	size_t elapsed = now - lastTimeChanged_;
	if ( elapsed > 1000 && val_ != this->value() ){
		lastTimeChanged_ = now;
		this->setValue( val_);
		//qDebug()<<"Outside changed value or value snmp delay! OIDDial::timerEvent";
	}
}

void OIDDial::fireSnmp(int val ){
	if ( !ConfigMgr::instance()->isOidEditable() ) {
		QString oid = ConfigMgr::instance()->getOid(objectName());
		SnmpNet::instance()->addAsyncSet( objectName().toStdString().c_str(), oid.toStdString().c_str(), "private", std::bind<SnmpCallbackFunc>( &OIDDial::snmpCallback, this, _1, _2, _3, _4) , val);
		lastTimeChanged_ = GetTickCount();
	}
}

SnmpCallback::RequestStatus OIDDial::snmpCallback( int , snmp_session*, snmp_pdu* pdu, SnmpObj* so){
	if (pdu->variables->type == ASN_INTEGER){
		val_ = *(u_long *) (pdu->variables->val.integer);
	}
	if ( so->var.type() )
		return SnmpCallback::RequestStop;
	else
		return SnmpCallback::RequestAgain;
}
