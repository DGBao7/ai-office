import "./styles/themes.css"

import Status from "./components/status/Status.jsx"

import History from "./components/history/History.jsx"

import Conversation from "./components/conversation/Conversation.jsx"

import UseInput from "./components/hooks/User.jsx"

import UseChat from "./components/hooks/Chat.jsx"

function App()
{
  const [user_input , _set_user_input] = UseInput()

  const [chat , _set_chat] = UseChat()

  console.log(chat)

  return (
    <>
      <div className="playground">
        <Status />

        <div className="workspace">
          <History />

          <Conversation 
            user_input={user_input}
            _set_user_input={_set_user_input}
            chat={chat}
            _set_chat={_set_chat}
          />
        </div>
      </div>
    </>
  )
}

export default App