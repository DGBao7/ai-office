import { useState } from "react";

function UseChat()
{
    const [chat , _set_chat] = useState([])

    return [chat , _set_chat]
}

export default UseChat