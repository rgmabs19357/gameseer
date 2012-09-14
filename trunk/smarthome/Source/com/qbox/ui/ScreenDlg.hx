package com.qbox.ui;
import nme.events.MouseEvent;
import base.ui.EmbedTextField;
import nme.text.TextFieldType;
import base.ui.ListDialogMgr;
import nme.display.Sprite;
import nme.display.Bitmap;
import base.data.DataLoader;
import base.ui.CommDialog;
import base.ui.ListDialog;

import com.qbox.logic.Qbox;
import com.qbox.logic.Screen;
import com.qbox.logic.QboxMgr;

import com.qbox.ui.osd.OsdFitnessDlg;
import com.qbox.ui.osd.OsdGroupDlg;
import com.qbox.ui.osd.OsdImgDlg;
import com.qbox.ui.osd.OsdOptionDlg;
import com.qbox.ui.osd.OsdSourceDlg;
import com.qbox.ui.osd.OsdSpecialDlg;
import com.qbox.ui.osd.OsdSysDlg;

class ScreenDlg extends ListDialog{

    var _pos:EmbedTextField;
    var _delete:EmbedTextField;
    var _screen:Screen;

    var _qboxip:EmbedTextField;
    //var _output:EmbedTextField;
    var _osdBtn:EmbedTextField;
    var _connBtn:EmbedTextField;
    var _s:Sprite;

    public function new ( dm:ListDialogMgr, c:Screen){
        super(dm);
        _screen = c;
        addChild( createElement());
    }

    public function onOsdBtnMouseClick( evt:MouseEvent ):Void{
        super.onMouseClick();
    }

    public override function onMouseClick():Void{ }

    //function onQboxMouseClick( evt:MouseEvent ):Void{ 
    //trace("Test");
        //var arr = QboxMgr.getInst()._qboxes;
        //for (i in 0...arr.length){
        //if ( _qboxip.text == arr[i]._ipv4){
        //var next = i+1;
        //if ( next == arr.length ){
        //next=0;
        //}
        //_screen._qboxip = _qboxip.text = arr[next]._ipv4;
        //break;
        //}
        //}
        //}
    /*
    function onOutputMouseClick( evt:MouseEvent ):Void{ 
        var arr = QboxMgr.getInst()._qboxes;
        for (i in 0...arr.length){
            if ( _qboxip.text == arr[i]._ipv4){
                var output:Int = Std.parseInt( _output.text.substr( 3, _output.text.length -2) );
                ++output;
                if ( output == Lambda.count(arr[i]._outputs)){
                    output = 0;
                }
                _screen._output = _output.text = "out"+output;
                break;
            }
        }
    }
    */

    function onConnBtnMouseClick( evt:MouseEvent ):Void{
#if neko
        if ( _connBtn.text == "disc"){
#else
        if ( _connBtn.text == "断开"){
#end
            _screen._qbox.close();
#if neko
            _connBtn.text = "conn";
#else
            _connBtn.text = "连接";
#end
            //trace("disconnect");
        }else{
            _screen._qbox._ipv4 = _qboxip.text;
            _screen._qbox.connect();
            //trace("connected");
            if (_screen._qbox._isFailed == false && _screen._qbox.isConected() ){
                _screen._qbox.connectedInit();
#if neko
                _connBtn.text = "disc";
#else
                _connBtn.text = "断开";
#end
            }
        }
    }

    override function show(){
        if ( _s != null) {
            if ( _qboxip != null){
                _s.removeChild(_qboxip);
                //_s.removeChild(_output);
                _s.removeChild(_pos);
                _s.removeChild(_osdBtn);
                _s.removeChild(_connBtn);
            }

            /*
               _output= new EmbedTextField();
               _output.selectable = false;
               _output.text = _screen._output;
               _output.scaleX = 3;
               _output.scaleY = 3;
               _output.width = 50;
               _output.height= 20;
               _output.x = 300;
               _output.addEventListener( MouseEvent.CLICK, onOutputMouseClick);
             */


            _pos= new EmbedTextField();
            _pos.selectable = false;
            _pos.text = "screen:" + _screen._col+"|"+_screen._row;
            _pos.type = INPUT;
            _pos.scaleX = 3;
            _pos.scaleY = 3;
            _pos.width = 50;
            _pos.height= 20;

            _osdBtn= new EmbedTextField();
            _osdBtn.selectable = false;
            _osdBtn.text = "OSD";
            _osdBtn.scaleX = 3;
            _osdBtn.scaleY = 3;
            _osdBtn.width = 20;
            _osdBtn.height= 18;
            _osdBtn.setBorder(true);
            _osdBtn.x = nme.Lib.current.stage.stageWidth - 80;
            _osdBtn.addEventListener( MouseEvent.CLICK, onOsdBtnMouseClick);

            _connBtn= new EmbedTextField();
            _connBtn.setBorder(true);
            _connBtn.selectable = false;
            if ( _screen._qbox._isFailed || !_screen._qbox.isConected() ){
#if neko
                _connBtn.text = "conn";
#else
                _connBtn.text = "连接";
#end
            }else{
#if neko
                _connBtn.text = "disc";
#else
                _connBtn.text = "断开";
#end
            }
            _connBtn.scaleX = 3;
            _connBtn.scaleY = 3;
            _connBtn.width = 20;
            _connBtn.height= 16;
            _connBtn.x = 320;
            _connBtn.addEventListener( MouseEvent.CLICK, onConnBtnMouseClick);

            _qboxip= new EmbedTextField();
            _qboxip.selectable = false;
            _qboxip.text = "127.0.0.1";
            _qboxip.type = INPUT;
            _qboxip.scaleX = 3;
            _qboxip.scaleY = 3;
            _qboxip.width = 50;
            _qboxip.height= 16;
            _qboxip.setBorder(true);
            _qboxip.x = 150;
            //_qboxip.addEventListener( MouseEvent.CLICK, onQboxMouseClick);

            _s.addChild( _pos);
            _s.addChild( _qboxip);
            //_s.addChild( _output);
            _s.addChild( _osdBtn);
            _s.addChild( _connBtn);
            _s.height = nme.Lib.current.stage.stageHeight/15;
        }
        return super.show();
    }
    override function hide(){
        if ( _s != null && _qboxip != null) {
            //_qboxip.removeEventListener(  MouseEvent.CLICK, onQboxMouseClick); 
            //_output.removeEventListener(  MouseEvent.CLICK, onOutputMouseClick); 
            _osdBtn.removeEventListener(  MouseEvent.CLICK, onOsdBtnMouseClick); 
            _connBtn.removeEventListener(  MouseEvent.CLICK, onConnBtnMouseClick); 
            _s.removeChild(_qboxip);
            _s.removeChild(_pos);
            //_s.removeChild(_output);
            _s.removeChild(_osdBtn);
            _s.removeChild(_connBtn);
            _qboxip = null;
            _pos= null;
            _osdBtn= null;
            _connBtn= null;
            //_output= null;
        }
        return super.hide();
    }

    public function createElement():Sprite{
        _s= new Sprite();

        //new OsdImgDlg(_listDialogMgr);
        //new OsdFitnessDlg( _listDialogMgr);
        //new OsdSourceDlg(_listDialogMgr);
        //new OsdOptionDlg(_listDialogMgr);
        //new OsdGroupDlg(_listDialogMgr);
        //new OsdSpecialDlg(_listDialogMgr);
        //new OsdSysDlg(_listDialogMgr);

        return _s;
    }
}
