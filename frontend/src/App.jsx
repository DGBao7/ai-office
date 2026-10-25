import "./styles/themes.css"

import Status from "./components/status/Status.jsx"

import History from "./components/history/History.jsx"

import Conversation from "./components/conversation/conversation.jsx"

function App()
{
  return (
    <>
      <div className="playground">
        <Status />

        <div className="workspace">
          <History />

          

          <Conversation />
        </div>
      </div>
    </>
  )
}

export default App