import { useRef } from "react";

import "./Input.css";

function InputContainer(
    {
        user_input , _set_user_input ,
        _set_chat
    }
)
{
    const textarea_ref = useRef(null);

    function _handle_change(event)
    {
        const textarea = event.target;

        _set_user_input(textarea.value);

        textarea.style.height = "24px";
        textarea.style.height = `${Math.min(textarea.scrollHeight, 200)}px`;
    }

    async function _handle_submit(event)
    {
        event.preventDefault();

        const content = user_input.trim();

        if (!content)
        {
            return;
        }

        _set_chat(
            current_chat => [
                ...current_chat,
                {
                    id: `user-${Date.now()}`,
                    role: "user",
                    content: content
                }
            ]
        );

        _set_user_input("");

        if (textarea_ref.current)
        {
            textarea_ref.current.style.height = "24px";
        }

        try
        {
            const response = await fetch(
                "http://127.0.0.1:8080/api/chat",
                {
                    method: "POST",

                    headers: {
                        "Content-Type": "application/json"
                    },

                    body: JSON.stringify({
                        message: content
                    })
                }
            );

            const data = await response.json();

            if (!response.ok)
            {
                throw new Error(data.error || "Request failed");
            }

            _set_chat(
                current_chat => [
                    ...current_chat,
                    {
                        id: `ai-${Date.now()}`,
                        role: "ai",
                        content: data.reply
                    }
                ]
            );
        }
        catch (error)
        {
            console.error("Chat request failed:", error);

            _set_chat(
                current_chat => [
                    ...current_chat,
                    {
                        id: `error-${Date.now()}`,
                        role: "ai",
                        content: "Không thể kết nối với backend."
                    }
                ]
            );
        }
    }

    function _handle_key_down(event)
    {
        if (event.key === "Enter" && !event.shiftKey)
        {
            event.preventDefault();
            event.currentTarget.form.requestSubmit();
        }
    }

    return (
        <form
            className="input_container"
            onSubmit={_handle_submit}
        >
            <textarea
                ref={textarea_ref}
                className="user_input"
                placeholder="Type..."
                value={user_input}
                onChange={_handle_change}
                onKeyDown={_handle_key_down}
                rows={1}
            />

            <button
                type="submit"
                className="send_button"
                disabled={!user_input.trim()}
                aria-label="Send"
            >
                ↑
            </button>
        </form>
    );
}

function Input(
    {
        user_input , _set_user_input ,
        chat , _set_chat
    }
)
{
    return (
        <div>
            <InputContainer
                user_input={user_input}
                _set_user_input={_set_user_input}
                _set_chat={_set_chat}
            />
        </div>
    );
}

export default Input;