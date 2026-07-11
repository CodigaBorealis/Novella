import './index.css'
import { Cog6ToothIcon } from "@heroicons/react/24/outline";
import WindowDecoration from './Components/WindowDecoration';

function App() {
  
  const buttons = [
    { icon: Cog6ToothIcon, action: () => window.electron.minimizeWindow() },
    { icon: Cog6ToothIcon, action: () => window.electron.minimizeWindow() },
    { icon: Cog6ToothIcon, action: () => window.electron.minimizeWindow() }
  ];

  return (
    <>
      <WindowDecoration buttons={buttons} />

    </>
  );
}

export default App
