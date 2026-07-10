import { contextBridge, ipcRenderer } from "electron";

contextBridge.exposeInMainWorld("novella",{
    
    selectProjectFile : ()=>ipcRenderer.invoke("select-project-file"),

    selectResourceFolder : ()=> ipcRenderer.invoke("select-resource-folder"),

    sendRequest: (payload: object)=>{

        return ipcRenderer.invoke("python-request", payload);
    },
});

