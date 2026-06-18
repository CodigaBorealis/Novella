#pragma once
#include <variant>
#include <vector>
#include <memory>
#include <string>

namespace Novella::Syntax::NovellaScript{

    struct ModuleImportDefinition;
    struct EngineImportDefinition;
    struct ModuleDefinition;
    struct FunctionDefinition;

    struct ArrayExpression;
    struct LiteralExpression;
    struct VariableExpression;
    struct FunctionCallExpression;
    struct UnaryExpression;
    struct BinaryExpression;
    struct MemberExpression;
    struct IndexExpression;
    struct PostFixExpression;

    struct ReturnStatement;
    struct IfStatement;
    struct VariableStatement;
    struct FunctionCallStatement;
    struct ExpressionStatement;
    struct AssignmentExpression;

    using Expression = std::variant<LiteralExpression, VariableExpression, FunctionCallExpression, UnaryExpression, BinaryExpression,
    AssignmentExpression, ArrayExpression, MemberExpression, IndexExpression, PostFixExpression>;
    using Statement = std::variant<ReturnStatement, IfStatement, VariableStatement, FunctionCallStatement, ExpressionStatement>;
    using Definition = std::variant<ModuleImportDefinition, EngineImportDefinition, ModuleDefinition, FunctionDefinition>;
}