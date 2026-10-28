import React , { useState } from "react";
import ReactMarkdown from "react-markdown";
import remarkGfm from "remark-gfm";

import { Prism as SyntaxHighlighter } from "react-syntax-highlighter";
import { vscDarkPlus } from "react-syntax-highlighter/dist/esm/styles/prism";

import "./MessageContent.css";

function SyntaxHighlight(
    {
        language , code
    }
)
{
    return (
        <SyntaxHighlighter
            language={language === "c++" ? "cpp" : language}
            style={vscDarkPlus}
            PreTag="div"
            customStyle={{
                margin: 0,
                padding: "16px",
                background: "transparent",
                fontSize: "13px",
                lineHeight: "1.65",
                overflowX: "auto"
            }}
        >
            {code}
        </SyntaxHighlighter>
    )
}

function CodeBlock(
    {
        language , code
    }
)
{
    const [copied , _set_copied] = useState(false)

    async function _copy_code()
    {
        try
        {
            await navigator.clipboard.writeText(code);
            _set_copied(true)
        }
        catch (error)
        {
            console.error("content/message copy code error: " + error)
        }
    }

    return (
        <div className="code_block">
            <div className="code_header">
                <span className="code_language">
                    {language}
                </span>

                <button
                    type="button"
                    className="code_copy_button"
                    onClick={_copy_code}
                >
                    {copied ? "Copied" : "Uncopied"}
                </button>
            </div>

            <SyntaxHighlight 
                language={language}
                code={code}
            />
        </div>
    )
}

function _render_code(
    {
        className , children
    }
)
{
    return (
        <code className={className}>
            {children}
        </code>
    )
}

function _render_pre({ children }) {
    const code_element = React.Children.toArray(children).find(
        child => React.isValidElement(child)
    );

    if (!code_element) {
        return <pre>{children}</pre>;
    }

    const class_name = code_element.props.className || "";
    const language_match = /language-([^\s]+)/.exec(class_name);
    const language = language_match ? language_match[1] : "text";

    const code = String(
        code_element.props.children ?? ""
    ).replace(/\n$/, "");

    return (
        <CodeBlock
            language={language}
            code={code}
        />
    );
}

function MessageContent(
    {content}
)
{
    return (
        <div className="message_content">
            <ReactMarkdown
                remarkPlugins={[remarkGfm]}
                components={{
                    pre : _render_pre ,
                    code : _render_code
                }}
            >
                {content || ""}
            </ReactMarkdown>
        </div>
    )
}

export default MessageContent