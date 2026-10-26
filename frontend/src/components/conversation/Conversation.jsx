import "./Conversation.css";

import Input from "./input/Input";

function Chat(
    {
        chat
    }
)
{
    return (
        <div className="chat">
            {chat.map((message , index) => (
                <div
                    key={message.id ?? index}
                    className={`message message_${message.role === "user" ? "user" : "ai"}`}
                >
                    <div className="message_content">
                        {message.content}
                    </div>
                </div>
            ))}
        </div>
    );
}

function Conversation(
    {
        user_input , _set_user_input ,
        chat , _set_chat
    }
)
{
    return (
        <div className="conversation">
            <Chat 
                chat={chat}
            />

            <Input 
                user_input={user_input}
                _set_user_input={_set_user_input}
                chat={chat}
                _set_chat={_set_chat}
            />
        </div>
    );
}

export default Conversation;