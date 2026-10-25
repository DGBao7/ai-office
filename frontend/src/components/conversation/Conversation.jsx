import "./Conversation.css";

function Conversation()
{
    return (
        <div className="conversation">
            <div className="message message_user">
                <div className="message_content">
                    Bon
                </div>
            </div>

            <div className="message message_ai">
                <div className="message_content">
                    Nana
                </div>
            </div>
        </div>
    );
}

export default Conversation;