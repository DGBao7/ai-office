#include "prompt/Prompt.h"

namespace prompt
{
    Prompt::Prompt() = default;

    void Prompt::_get_user_input(std::string input)
    {
        this -> input = input;
    }

    nlohmann::json Prompt::_return_prompt(std::string role)
    {
        nlohmann::json output_schema;
        std::string instructions;

        if (role == "software architect")
        {
            instructions =
                "You are a Software Architect. Analyze the requirements, "
                "design the software architecture, identify components, "
                "data flow, technical risks, and implementation steps.";

            output_schema = {
                {"type", "object"},
                {"additionalProperties", false},
                {"properties", {
                    {"summary", {
                        {"type", "string"}
                    }},
                    {"requirements", {
                        {"type", "array"},
                        {"items", {{"type", "string"}}}
                    }},
                    {"architecture", {
                        {"type", "object"},
                        {"additionalProperties", false},
                        {"properties", {
                            {"components", {
                                {"type", "array"},
                                {"items", {
                                    {"type", "object"},
                                    {"additionalProperties", false},
                                    {"properties", {
                                        {"name", {{"type", "string"}}},
                                        {"responsibility", {{"type", "string"}}},
                                        {"interfaces", {
                                            {"type", "array"},
                                            {"items", {{"type", "string"}}}
                                        }}
                                    }},
                                    {"required", {
                                        "name",
                                        "responsibility",
                                        "interfaces"
                                    }}
                                }}
                            }},
                            {"data_flow", {
                                {"type", "array"},
                                {"items", {{"type", "string"}}}
                            }},
                            {"design_decisions", {
                                {"type", "array"},
                                {"items", {{"type", "string"}}}
                            }}
                        }},
                        {"required", {
                            "components",
                            "data_flow",
                            "design_decisions"
                        }}
                    }},
                    {"technical_risks", {
                        {"type", "array"},
                        {"items", {{"type", "string"}}}
                    }},
                    {"implementation_plan", {
                        {"type", "array"},
                        {"items", {{"type", "string"}}}
                    }},
                    {"assumptions", {
                        {"type", "array"},
                        {"items", {{"type", "string"}}}
                    }}
                }},
                {"required", {
                    "summary",
                    "requirements",
                    "architecture",
                    "technical_risks",
                    "implementation_plan",
                    "assumptions"
                }}
            };
        }
        else if (role == "software engineer")
        {
            instructions =
                "You are a Software Engineer. Implement the requirements "
                "using the provided architecture when available. "
                "Write maintainable code, preserve existing constraints, "
                "and identify any assumptions. Put the complete code of "
                "each file in its code field.";

            output_schema = {
                {"type", "object"},
                {"additionalProperties", false},
                {"properties", {
                    {"summary", {
                        {"type", "string"}
                    }},
                    {"files", {
                        {"type", "array"},
                        {"items", {
                            {"type", "object"},
                            {"additionalProperties", false},
                            {"properties", {
                                {"file_path", {{"type", "string"}}},
                                {"purpose", {{"type", "string"}}},
                                {"code", {{"type", "string"}}}
                            }},
                            {"required", {
                                "file_path",
                                "purpose",
                                "code"
                            }}
                        }}
                    }},
                    {"implementation_notes", {
                        {"type", "array"},
                        {"items", {{"type", "string"}}}
                    }},
                    {"assumptions", {
                        {"type", "array"},
                        {"items", {{"type", "string"}}}
                    }}
                }},
                {"required", {
                    "summary",
                    "files",
                    "implementation_notes",
                    "assumptions"
                }}
            };
        }
        else if (role == "qa engineer")
        {
            instructions =
                "You are a Software Engineer and coding assistant. "
                "Implement the user's request directly. "
                "When asked to write code, provide complete, working code "
                "in the requested programming language. "
                "Do not review code unless explicitly requested. "
                "Respond in plain text using Markdown when appropriate. "
                "Do not return JSON.";

            return {
                {"role", "coder"},
                {"instructions", instructions},
                {"user_request", this -> input}
            };
        }
        else if (role == "task evaluator")
        {
            instructions =
                "You are a Task Evaluator and Software Engineer. "
                "Your responsibility is to evaluate the complexity of the user's request "
                "and decide whether to handle it directly or delegate it. "

                "Evaluate task difficulty on a scale from 0 to 100. "
                "Consider the number of components, logical complexity, "
                "dependencies, integrations, and architectural requirements. "

                "Use the following guidelines: "
                "0-25: Very simple tasks. "
                "26-50: Basic tasks with multiple steps. "
                "51-75: Moderate tasks with some complexity. "
                "76-100: Complex tasks requiring architectural planning or multiple components. "

                "If difficulty_score is 75 or below, implement the request directly. "
                "Choose the simplest correct solution that satisfies the requirements. "
                "Prefer straightforward logic and beginner-friendly syntax when appropriate. "
                "Avoid unnecessary abstractions, classes, design patterns, "
                "dependencies, and additional features. "
                "Do not overcomplicate simple programming tasks. "

                "If difficulty_score is above 75, do not implement the task. "
                "Leave the result field empty so the task can be delegated."
                
                " The difficulty_score must always be a JSON integer. "
                " Never write numbers as words. "
                " For example, use 30 instead of thirty. "
                " The response must be valid JSON and must follow output_schema exactly. "
                " Never include source code or explanations outside the result field. "

                "RESPONSE FORMATTING RULES: "
                "Choose the response format based on the user's request. "

                "For ordinary conversations, greetings, simple questions, "
                "and short answers, use natural plain text. "
                "Do not add headings, titles, labels, bullet points, "
                "numbered lists, or unnecessary Markdown formatting. "

                "For explanations involving multiple topics or complex information, "
                "use Markdown headings, lists, or tables only when they improve readability. "

                "When providing source code, always use fenced code blocks "
                "with the correct language identifier, such as ```python, "
                "```cpp, or ```javascript. "

                " Before presenting source code, explicitly state the programming language "
                "being used. "
                "Use the format: 'Ngôn ngữ sử dụng: C++'. "
                "If the user specifies a programming language, always use that language. "
                "If the user does not specify one, infer it from the provided code "
                "or conversation context when possible. "
                "If the language cannot be determined, ask the user instead of "
                "arbitrarily choosing one. "
                "Always specify the correct language identifier in code fences, "
                "such as cpp, python, javascript, or java. "

                "When presenting code in multiple programming languages, "
                "use a separate heading and code block for each language. "

                "Do not present source code as unformatted plain text. "
                "Do not force Markdown formatting into every response. "
                "Do not add artificial sections such as 'Response', "
                "'Answer', or 'Conclusion'. "

                "Keep explanations concise, natural, and relevant. "
                "Do not add unnecessary sections or explanations. "

                "The result field must contain the complete response. "
                "The overall response must still be valid JSON matching output_schema. "
                "Do not use Markdown code fences around the outer JSON response. "

                "Keep the assessment concise. "
                "Return only valid JSON matching output_schema.";

            output_schema = {
                {"type", "object"},
                {"additionalProperties", false},
                {"properties", {
                    {"difficulty_score", {
                        {"type", "integer"},
                        {"minimum", 0},
                        {"maximum", 100}
                    }},
                    {"assessment", {
                        {"type", "string"}
                    }},
                    {"result", {
                        {"type", "string"}
                    }}
                }},
                {"required", {
                    "difficulty_score",
                    "assessment",
                    "result"
                }}
            };
        }
        
        return {
            {"role", role},
            {"instructions",
                instructions +
                " Return only valid JSON matching output_schema. "
                "Do not use Markdown code fences or add text outside the JSON."},
            {"user_request", this -> input},
            {"output_schema", output_schema}
        };
    }
}