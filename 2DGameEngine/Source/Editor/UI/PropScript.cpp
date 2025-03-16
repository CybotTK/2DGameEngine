#include "Editor/UI/Props.h"

#include "Editor/ImGui/imgui.h"

#define USE_TEXT_EDITOR 0 // TEXT EDITOR IS SUPER S**T I DON'T LIKE IT

#if USE_TEXT_EDITOR
#include "Editor/ImGui/TextEditor.h"

static ::TextEditor __editor;

void SetPythonLang() {
    static bool _alreadySet = false;
    if (_alreadySet) {
        return;
    }
    _alreadySet = true;

    TextEditor::LanguageDefinition langDef;

    static const char* const keywords[] = {
    "False", "None", "True", "and", "as", "assert", "async", "await", "break",
    "class", "continue", "def", "del", "elif", "else", "except", "finally", "for",
    "from", "global", "if", "import", "in", "is", "lambda", "nonlocal", "not",
    "or", "pass", "raise", "return", "try", "while", "with", "yield",
    "__class__", "__delattr__", "__dict__", "__dir__", "__doc__", "__eq__",
    "__format__", "__ge__", "__getattribute__", "__gt__", "__hash__",
    "__init__", "__le__", "__lt__", "__module__", "__ne__", "__new__",
    "__reduce__", "__reduce_ex__", "__repr__", "__setattr__", "__sizeof__",
    "__str__", "__subclasshook__", "__weakref__"
    };

    for (auto& k : keywords) langDef.mKeywords.insert(k);

    static const char* const identifiers[] = {
        "abs", "all", "any", "ascii", "bin", "bool", "bytearray", "bytes", "breakpoint",
        "callable", "chr", "classmethod", "compile", "complex", "delattr", "dict",
        "dir", "divmod", "enumerate", "eval", "exec", "filter", "float", "format",
        "frozenset", "getattr", "globals", "hasattr", "hash", "help", "hex", "id",
        "input", "int", "isinstance", "issubclass", "iter", "len", "list", "locals",
        "map", "max", "memoryview", "min", "next", "object", "oct", "open",
        "ord", "pow", "print", "property", "range", "repr", "reversed", "round",
        "set", "setattr", "slice", "sorted", "staticmethod", "str", "sum",
        "super", "tuple", "type", "vars", "zip", "__import__"
    };

    for (auto& k : identifiers) {
        TextEditor::Identifier id;
        id.mDeclaration = "Built-in function";
        langDef.mIdentifiers.insert(std::make_pair(std::string(k), id));
    }

    langDef.mTokenRegexStrings.push_back(std::make_pair<std::string, TextEditor::PaletteIndex>(
        "[ \\t]*#[^\n]*", TextEditor::PaletteIndex::Comment));  // Comments

    langDef.mTokenRegexStrings.push_back(std::make_pair<std::string, TextEditor::PaletteIndex>(
        "L?\\\"(\\\\.|[^\\\\\"])*\\\"", TextEditor::PaletteIndex::String));  // Double-quoted strings

    langDef.mTokenRegexStrings.push_back(std::make_pair<std::string, TextEditor::PaletteIndex>(
        "L?\\'(\\\\.|[^\\\\'])*\\'", TextEditor::PaletteIndex::String));  // Single-quoted strings

    langDef.mTokenRegexStrings.push_back(std::make_pair<std::string, TextEditor::PaletteIndex>(
        "[+-]?([0-9]+\\.[0-9]*|\\.[0-9]+|[0-9]+)", TextEditor::PaletteIndex::Number));  // Floating-point numbers

    langDef.mTokenRegexStrings.push_back(std::make_pair<std::string, TextEditor::PaletteIndex>(
        "0[bB][01]+", TextEditor::PaletteIndex::Number));  // Binary numbers

    langDef.mTokenRegexStrings.push_back(std::make_pair<std::string, TextEditor::PaletteIndex>(
        "0[oO][0-7]+", TextEditor::PaletteIndex::Number));  // Octal numbers

    langDef.mTokenRegexStrings.push_back(std::make_pair<std::string, TextEditor::PaletteIndex>(
        "0[xX][0-9a-fA-F]+", TextEditor::PaletteIndex::Number));  // Hexadecimal numbers

    langDef.mTokenRegexStrings.push_back(std::make_pair<std::string, TextEditor::PaletteIndex>(
        "[a-zA-Z_][a-zA-Z0-9_]*", TextEditor::PaletteIndex::Identifier));  // Identifiers (variable names, function names, etc.)

    langDef.mTokenRegexStrings.push_back(std::make_pair<std::string, TextEditor::PaletteIndex>(
        "[\\[\\]\\{\\}\\(\\)]", TextEditor::PaletteIndex::Punctuation));  // Brackets and parentheses


    langDef.mCommentStart = R"(""")";
    langDef.mCommentEnd = R"(""")";
    langDef.mSingleLineComment = "#";

    langDef.mCaseSensitive = true;
    langDef.mAutoIndentation = true;

    langDef.mName = "Python";

    __editor.SetLanguageDefinition(langDef);
}
#else   // USE_TEXT_EDITOR
#define MULTILINE_TEXT_SIZE 8192 
#endif  // USE_TEXT_EDITOR

void ui::PropScript(const std::string& name, std::string* script) {
#if USE_TEXT_EDITOR
    SetPythonLang();

    if (ui::Header("Editor")) {
        __editor.SetText(*script);
        __editor.Render("Script Editor", { ui::GetRemainingWidth(), ui::GetRemainingHeight() }, 1.f);
        *script = __editor.GetText();
        script->erase(script->end() - 1, script->end());
    }
#else // USE_TEXT_EDITOR
    char buf[MULTILINE_TEXT_SIZE];

    if (script->size() < MULTILINE_TEXT_SIZE - 2) {
        strcpy_s(buf, script->c_str());
        ImGui::InputTextMultiline(
            "##ConstructionScript",
            buf, MULTILINE_TEXT_SIZE,
            { ui::GetRemainingWidth(), ui::GetRemainingHeight() }
        );
        *script = buf;
    }
    else {
        ImGui::Text("Text is too big!");
    }
#endif // USE_TEXT_EDITOR
}