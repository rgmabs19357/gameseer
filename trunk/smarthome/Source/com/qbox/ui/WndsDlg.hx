package com.qbox.ui;

import base.ui.FixedDlg;
import base.ui.ListFixedDlg;
import base.ui.CommDialogMgr;
import base.ui.ListDialogMgr;
import nme.display.Sprite;
import nme.display.Bitmap;
import base.data.DataLoader;
import com.qbox.logic.WndMgr;
import com.qbox.logic.Wnd;

import com.pictionary.ui.DrawingDlgMgr;
class WndsDlg extends ListFixedDlg{
    public function new ( dm:CommDialogMgr ){
        super(dm, new Bitmap( DataLoader.getInst().bms_.get("wnd")));

        x = 250;
        y= nme.Lib.current.stage.stageHeight - 80;

        //new PlusItemFixedDlg(_listDialogMgr, cbPlusWnd);
    }

    public function cbPlusWnd( ):Void{
        var qd = new WndDlg(_listDialogMgr, WndMgr.getInst().createWnd());
        qd.show();
    }

    public override function onMouseClick( ):Void{
        if ( _mgr.isAnimating() == false){
            _listDialogMgr.removeAllMovables();

            for ( c in WndMgr.getInst()._wnds){
                new WndDlg(_listDialogMgr, c);
            }
        }
        super.onMouseClick();
    }
}
