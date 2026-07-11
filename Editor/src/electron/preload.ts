import { contextBridge, ipcRenderer } from "electron";

contextBridge.exposeInMainWorld("novella",{
    
    minimizeWindow : ()=> ipcRenderer.send("window-minimize"),
    
    maximizeWindow : ()=>ipcRenderer.send("window-maximize"),
    
    closeWindow : ()=> ipcRenderer.send("close-window"),

    selectProjectFile : ()=>ipcRenderer.invoke("select-project-file"),

    selectResourceFolder : ()=> ipcRenderer.invoke("select-resource-folder"),

    sendRequest: (payload: object)=>{

        return ipcRenderer.invoke("python-request", payload);
    },
});

