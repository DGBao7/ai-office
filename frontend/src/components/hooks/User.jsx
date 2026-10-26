import { useState } from "react"

function UseInput()
{   
    const [user_input , _set_user_input] = useState("")

    return [user_input , _set_user_input]
}

export default UseInput