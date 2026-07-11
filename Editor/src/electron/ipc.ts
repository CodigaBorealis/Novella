import { BrowserWindow, ipcMain } from "electron";

export function registerIpcHandlers() : void{

    ipcMain.on("window-minimize", ()=>{
    
        BrowserWindow.getFocusedWindow()?.minimize();
    });
    
    ipcMain.on("window-maximize", ()=>{
    
        const window = BrowserWindow.getFocusedWindow();
    
        if(!window) return;
    
        if(window.isMaximized()){
    
            window.unmaximize();
    
        }else{
    
            window.maximize();
        }
    
    });
    
    ipcMain.on("window-close", ()=>{
    
        BrowserWindow.getFocusedWindow()?.close();
    });
}