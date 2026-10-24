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
                "You are a QA Engineer. Review the requirements, architecture, "
                "and code provided. Identify defects, edge cases, and "
                "requirement violations. Suggest test cases. Do not claim "
                "that tests were executed unless execution evidence is provided. "
                "Use insufficient_information when there is not enough evidence "
                "to determine readiness.";

            output_schema = {
                {"type", "object"},
                {"additionalProperties", false},
                {"properties", {
                    {"verdict", {
                        {"type", "string"},
                        {"enum", {
                            "ready",
                            "needs_changes",
                            "insufficient_information"
                        }}
                    }},
                    {"summary", {
                        {"type", "string"}
                    }},
                    {"findings", {
                        {"type", "array"},
                        {"items", {
                            {"type", "object"},
                            {"additionalProperties", false},
                            {"properties", {
                                {"severity", {
                                    {"type", "string"},
                                    {"enum", {
                                        "critical",
                                        "high",
                                        "medium",
                                        "low"
                                    }}
                                }},
                                {"location", {{"type", "string"}}},
                                {"issue", {{"type", "string"}}},
                                {"recommendation", {{"type", "string"}}}
                            }},
                            {"required", {
                                "severity",
                                "location",
                                "issue",
                                "recommendation"
                            }}
                        }}
                    }},
                    {"test_cases", {
                        {"type", "array"},
                        {"items", {
                            {"type", "object"},
                            {"additionalProperties", false},
                            {"properties", {
                                {"name", {{"type", "string"}}},
                                {"steps", {
                                    {"type", "array"},
                                    {"items", {{"type", "string"}}}
                                }},
                                {"expected_result", {{"type", "string"}}},
                                {"execution_status", {
                                    {"type", "string"},
                                    {"enum", {
                                        "not_run",
                                        "passed",
                                        "failed"
                                    }}
                                }}
                            }},
                            {"required", {
                                "name",
                                "steps",
                                "expected_result",
                                "execution_status"
                            }}
                        }}
                    }}
                }},
                {"required", {
                    "verdict",
                    "summary",
                    "findings",
                    "test_cases"
                }}
            };
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