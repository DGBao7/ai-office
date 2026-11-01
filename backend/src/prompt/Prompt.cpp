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
                "You are a Software Architect. Analyze the user's requirements "
                "and propose an architecture appropriate to the task complexity. "

                "Prioritize simplicity over unnecessary abstraction. "
                "For simple tasks, use a minimal design with as few components "
                "as possible. Do not introduce unnecessary classes, interfaces, "
                "design patterns, layers, or dependencies. "

                "For basic programming exercises and algorithms, avoid "
                "overengineering. A simple function or standalone implementation "
                "may be sufficient. "

                "Only identify relevant requirements, components, data flow, "
                "technical risks, and implementation steps. "
                "Do not invent requirements, risks, or architectural decisions. "
                "Use empty arrays when there is nothing relevant to report.";

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
                "You are a Software Engineer. Implement the user's requirements "
                "using the provided architecture when available. "

                "Choose the simplest correct solution that satisfies the request. "
                "Match the code complexity to the problem complexity. "

                "For basic programming exercises and algorithms: "
                "- Prefer straightforward logic and beginner-friendly syntax. "
                "- Avoid unnecessary classes, inheritance, interfaces, and abstractions. "
                "- Do not introduce design patterns or additional dependencies. "
                "- Do not add features that were not requested. "
                "- Avoid splitting simple solutions into multiple files. "

                "Write readable and maintainable code without overengineering. "
                "Preserve existing project constraints. "
                "Keep implementation notes and assumptions concise. "
                "Use empty arrays when there is nothing relevant to report. "
                "Put the complete code of each file in its code field.";

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

                "Always choose the simplest correct implementation. "
                "For basic algorithms and programming exercises, "
                "use straightforward logic and beginner-friendly code. "

                "Do not introduce unnecessary classes, abstractions, "
                "design patterns, additional files, or dependencies. "
                "Do not add functionality beyond the user's request. "

                "Provide complete, working code in the requested language. "
                "Keep explanations brief and relevant. "
                "Use Markdown when appropriate. "
                "Do not return JSON.";

            // output_schema = {
            //     {"type", "object"},
            //     {"additionalProperties", false},
            //     {"properties", {
            //         {"verdict", {
            //             {"type", "string"},
            //             {"enum", {
            //                 "ready",
            //                 "needs_changes",
            //                 "insufficient_information"
            //             }}
            //         }},
            //         {"summary", {
            //             {"type", "string"}
            //         }},
            //         {"findings", {
            //             {"type", "array"},
            //             {"items", {
            //                 {"type", "object"},
            //                 {"additionalProperties", false},
            //                 {"properties", {
            //                     {"severity", {
            //                         {"type", "string"},
            //                         {"enum", {
            //                             "critical",
            //                             "high",
            //                             "medium",
            //                             "low"
            //                         }}
            //                     }},
            //                     {"location", {{"type", "string"}}},
            //                     {"issue", {{"type", "string"}}},
            //                     {"recommendation", {{"type", "string"}}}
            //                 }},
            //                 {"required", {
            //                     "severity",
            //                     "location",
            //                     "issue",
            //                     "recommendation"
            //                 }}
            //             }}
            //         }},
            //         {"test_cases", {
            //             {"type", "array"},
            //             {"items", {
            //                 {"type", "object"},
            //                 {"additionalProperties", false},
            //                 {"properties", {
            //                     {"name", {{"type", "string"}}},
            //                     {"steps", {
            //                         {"type", "array"},
            //                         {"items", {{"type", "string"}}}
            //                     }},
            //                     {"expected_result", {{"type", "string"}}},
            //                     {"execution_status", {
            //                         {"type", "string"},
            //                         {"enum", {
            //                             "not_run",
            //                             "passed",
            //                             "failed"
            //                         }}
            //                     }}
            //                 }},
            //                 {"required", {
            //                     "name",
            //                     "steps",
            //                     "expected_result",
            //                     "execution_status"
            //                 }}
            //             }}
            //         }}
            //     }},
            //     {"required", {
            //         "verdict",
            //         "summary",
            //         "findings",
            //         "test_cases"
            //     }}
            // };
        }
        else
        {
            return {
                {"error", "Unknown role"},
                {"supported_roles", {
                    "software_architect",
                    "software_engineer",
                    "qa_engineer"
                }}
            };
        }

        if (role == "qa engineer")
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