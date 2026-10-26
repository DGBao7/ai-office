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

    function _handle_submit(event)
    {
        event.preventDefault();

        const content = user_input.trim();

        if (!content)
        {
            return;
        }

        _set_chat(
            current_chat => [
                ...current_chat ,
                {
                    id: Date.now() ,
                    role: "user" ,
                    content: content
                }
            ]
        );

        _set_user_input("");

        if (textarea_ref.current)
        {
            textarea_ref.current.style.height = "24px";
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