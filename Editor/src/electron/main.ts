import { app, BrowserWindow, session } from 'electron';
import path from 'path';
import { isDev } from './util.js';
import { fileURLToPath } from 'url';
import { registerIpcHandlers } from './ipc.js';

const __filename = fileURLToPath(import.meta.url);
const __dirname = path.dirname(__filename);

main();

function main(): void {

    registerAppEvents();
}

function registerAppEvents(): void {

    app.whenReady().then(() => {

        configureSecurity();
        registerIpcHandlers();
        createWindow();

    })

    app.on("window-all-closed", () => {

        if (process.platform !== "darwin") {

            app.quit();
        }
    })
}

function createWindow(): void {

    const mainWindow = new BrowserWindow({

        frame: false,

        webPreferences: {

            preload: path.join(__dirname, "preload.js"),

            nodeIntegration: false,
            contextIsolation: true,
            sandbox: true,
        }
    })

    if (isDev()) {

        mainWindow.loadURL('http://localhost:5123');

    } else {

        mainWindow.loadFile(path.join(app.getAppPath() + "/dist-react/index.html"));
    }
}

function configureSecurity(): void {

    app.on("web-contents-created", (_, contents) => {

        contents.on("will-navigate", (event, url) => {

            if (isDev() && url.startsWith("http://localhost:5123")) {

                return;
            }

            event.preventDefault();

        });

        contents.setWindowOpenHandler(() => ({

            action: "deny"

        }

        ));

        contents.on("will-attach-webview", (event) => {

            event.preventDefault();
        });

    })


    session.defaultSession.webRequest.onBeforeRequest(

        { urls: ["*://*/*"] }, (details, callback) => {

            const url = new URL(details.url);

            if (url.hostname === "localhost" && isDev()) {

                callback({ cancel: false });

                return;
            }

            callback({ cancel: true });
        }
    );
}

