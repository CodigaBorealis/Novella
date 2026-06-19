#include "../Novella/Syntax/NovellaScript/Parser.hpp"
#include "../Novella/Syntax/NovellaScript/Lexer.hpp"
#include "../Novella/Syntax/NovellaScript/Script.hpp"
#include "../Novella/Syntax/NovellaScript/Definition.hpp"
#include <memory>
#include <stdexcept>
#include <string>
#include <variant>
#include <vector>
#include <iostream>

namespace Novella::Syntax::NovellaScript{

    Parser::Parser(Lexer& lexer){

        while(true){

            Token token = lexer.next();

            tokens.push_back(token);

            if(token.type == Token::Type::EndOfFile) break;
        }
    }
    
    Token& Parser::current(){

        return tokens[position];
    }

    Token& Parser::peek(size_t offset){

        if(position + offset >= tokens.size()) return tokens.back();

        return tokens[position + offset];
    }

    void Parser::consume(){

        static std::string parsed;

        //std::system("clear");
        parsed += current().text + "\n";
        
        if(position < tokens.size() - 1) ++ position;

        //std::cout << "PARSED TOKENS:\n" << parsed << "\n";

        
    }

    void Parser::expect(Token::Type type){

        if(current().type != type) throw std::runtime_error("Unexpected token: " + current().text + " at position " + std::to_string(position) + " Token: " + current().text);

        consume();

    }

    Script Parser::parse(){

        return parseScript();
    }

    Expression Parser::parseUnary(){

        if(current().type == Token::Type::Increment){

            consume();

            Expression operand = parseUnary();
            
            if(!std::holds_alternative<VariableExpression>(operand) && !std::holds_alternative<MemberExpression>(operand) && !std::holds_alternative<IndexExpression>(operand)){

                throw std::runtime_error("Invalid '++' operand at " + std::to_string(position) + " Token: " + current().text);
            }
            
            UnaryExpression unary{};

            unary.operand = std::make_unique<Expression>(std::move(operand));

            unary.operation = Token::Type::Increment;
            
            return unary;

        }else if(current().type == Token::Type::Decrement){

            consume();

            Expression operand = parseUnary();
            
            if(!std::holds_alternative<VariableExpression>(operand) && !std::holds_alternative<MemberExpression>(operand) && !std::holds_alternative<IndexExpression>(operand)){

                throw std::runtime_error("Invalid '--' operand at " + std::to_string(position) + " Token: " + current().text);
            }
            
            UnaryExpression unary{};

            unary.operand = std::make_unique<Expression>(std::move(operand));

            unary.operation = Token::Type::Decrement;
            
            return unary;

        }

        if(current().type == Token::Type::Not || current().type == Token::Type::Minus){

            Token::Type operation = current().type;

            consume();

            UnaryExpression expression{};

            expression.operation = operation;
            expression.operand = std::make_unique<Expression>(parseUnary());

            return expression;
        }

        return parsePostFix();
    }

    Expression Parser::parseFactor(){

        Expression expression = parseUnary();

        while(current().type == Token::Type::Multiply || current().type == Token::Type::Divide || current().type == Token::Type::Modulo){

            Token::Type operation = current().type;

            consume();

            BinaryExpression binary{};

            binary.left = std::make_unique<Expression>(std::move(expression));
            binary.operation = operation;
            binary.right = std::make_unique<Expression>(parseUnary());

            expression = std::move(binary);
        }

        return expression;
    }

    Expression Parser::parseTerm(){

        Expression expression = parseFactor();

        while(current().type == Token::Type::Plus || current().type == Token::Type::Minus){

            Token::Type operation =  current().type;

            consume();

            BinaryExpression binary{};

            binary.left = std::make_unique<Expression>(std::move(expression));
            binary.operation = operation;
            binary.right = std::make_unique<Expression>(parseFactor());

            expression = std::move(binary);
        }

        return expression;
    }

    Expression Parser::parseComparison(){

        Expression expression = parseTerm();

        while(current().type == Token::Type::Less || current().type == Token::Type::LessEquals || current().type == Token::Type::Greater || current().type == Token::Type::GreaterEquals){

            Token::Type operation = current().type;
            
            consume();

            BinaryExpression binary{};

            binary.left = std::make_unique<Expression>(std::move(expression));
            binary.operation = operation;
            binary.right = std::make_unique<Expression>(parseTerm());

            expression = std::move(binary);            
        }

        return expression;
    }

    Expression Parser::parseEquality(){

        Expression expression = parseComparison();

        while(current().type == Token::Type::Equals || current().type == Token::Type::NotEquals){

            Token::Type operation = current().type;

            consume();

            BinaryExpression binary{};

            binary.left = std::make_unique<Expression>(std::move(expression));
            binary.operation = operation;
            binary.right = std::make_unique<Expression>(parseComparison());

            expression = std::move(binary); 
        }

        return expression;
    }

    Expression Parser::parseLogicalAnd(){

        Expression expression = parseEquality();
        
        while(current().type == Token::Type::And){

            Token::Type operation = current().type;

            consume();

            BinaryExpression binary{};

            binary.left = std::make_unique<Expression>(std::move(expression));
            binary.operation = operation;
            binary.right = std::make_unique<Expression>(parseEquality());

            expression = std::move(binary);
        }

        return expression;
    }

    Expression Parser::parseLogicalOr(){

        Expression expression = parseLogicalAnd();

        while(current().type == Token::Type::Or){

            Token::Type operation = current().type;

            consume();

            BinaryExpression binary{};

            binary.left = std::make_unique<Expression>(std::move(expression));
            binary.operation = operation;
            binary.right = std::make_unique<Expression>(parseLogicalAnd());

            expression = std::move(binary);
        }

        return expression;
    }

    Expression Parser::parsePrimary(){

        if(current().type == Token::Type::Number){

            double value = std::stod(current().text);

            consume();

            LiteralExpression expression{};

            expression.value.type = Value::Type::Number;
            expression.value.underlyingValue = value;

            return expression;
        }

        if(current().type == Token::Type::Boolean){

            if(current().text != "true" && current().text != "false") throw std::runtime_error("Boolean values can only be 'true' or 'false' at " + std::to_string(position) + " Token: " + current().text);

            bool value;

            current().text == "true" ? value = true : value = false;

            consume();

            LiteralExpression expression{};

            expression.value.type = Value::Type::Boolean;
            expression.value.underlyingValue = value;

            return expression;

        }

        if(current().type == Token::Type::String){

            std::string value = current().text;

            consume();

            LiteralExpression expresion{};

            expresion.value.type = Value::Type::String;
            expresion.value.underlyingValue = value;

            return expresion;
        }

        if(current().type == Token::Type::Identifier){

            std::string name = current().text;
            
            consume();

            return VariableExpression{name};
        }

        if(current().type == Token::Type::LParen){

            consume();

            Expression expression = parseExpression();

            expect(Token::Type::RParen);

            return expression;
        }

        if(current().type == Token::Type::LBracket){

            return parseArrayExpression();
        }

        throw std::runtime_error("Expected expression at " + std::to_string(position) + " Token: " + current().text);
    }

    Expression Parser::parseAssignment(){

        Expression left = parseLogicalOr();

        if(current().type == Token::Type::Assign){

            if(!std::holds_alternative<VariableExpression>(left) && !std::holds_alternative<MemberExpression>(left) && !std::holds_alternative<IndexExpression>(left)){

                throw std::runtime_error("Invalid assigment target at " + std::to_string(position) + " Token: " + current().text);
            }

            consume();

            Expression value = parseAssignment();

            AssignmentExpression assignment{};

            assignment.variable = std::make_unique<Expression>(std::move(left));
            assignment.value = std::make_unique<Expression>(std::move(value));

            return assignment;

        }

        return left;
    }

    ReturnStatement Parser::parseReturn(){

        expect(Token::Type::Return);

        Expression value{};

        if(current().type != Token::Type::SemiColon){

            value = parseExpression();
        }

        expect(Token::Type::SemiColon);

        return ReturnStatement{std::move(value)};
    }

    IfStatement Parser::parseIf(){

        expect(Token::Type::If);

        Expression condition = parseExpression();

        expect(Token::Type::Then);

        IfStatement statement{};

        statement.condition = std::move(condition);

        while(current().type != Token::Type::Else && current().type != Token::Type::EndIf && current().type != Token::Type::EndOfFile){

            statement.body.push_back(parseStatement());
        }

        if(current().type == Token::Type::Else){

            consume();

            while(current().type != Token::Type::EndIf && current().type != Token::Type::EndOfFile){

                statement.elseBody.push_back(parseStatement());
            }
        }

        expect(Token::Type::EndIf);

        return statement;
    }

    VariableStatement Parser::parseVariable(){

        expect(Token::Type::Var);

        std::string name = current().text;

        expect(Token::Type::Identifier);

        Expression initializer{};

        expect(Token::Type::Assign);

        initializer = parseExpression();

        expect(Token::Type::SemiColon);

        return VariableStatement{name, std::move(initializer)};

    }

    Script Parser::parseScript(){

        Script script{};

        while(current().type != Token::Type::EndOfFile){

            if(current().type == Token::Type::Import){
                //To paste the contents from the other module into this struct
                script.definitions.push_back(parseImport());

            }else{

                script.definitions.push_back(parseDefinition());

            }
        }

        return script;

    }

    ExpressionStatement Parser::parseExpressionStatement(){

        ExpressionStatement statement{};
        
        statement.expression = parseExpression();

        expect(Token::Type::SemiColon);

        return statement;
    }
    
    Expression Parser::parseArrayExpression(){

        ArrayExpression array{};

        expect(Token::Type::LBracket);

        if(current().type != Token::Type::RBracket){

            while(true){

                array.elements.push_back(parseExpression());

                if(current().type == Token::Type::RBracket) break;

                expect(Token::Type::Comma);
            }
        }

        expect(Token::Type::RBracket);

        return array;
        
    }
//This is hell
    Expression Parser::parsePostFix(){

        Expression expression = parsePrimary();

        while(true){

            if(current().type == Token::Type::Dot){

                consume();

                std::string member = current().text;
                
                expect(Token::Type::Identifier);

                MemberExpression access{};

                access.object = std::make_unique<Expression>(std::move(expression));

                access.member = member;

                expression = std::move(access);

            }else if(current().type == Token::Type::LParen){

                FunctionCallExpression call{};

                call.answer = std::make_unique<Expression>(std::move(expression));

                consume();

                if(current().type != Token::Type::RParen){

                    while(true){

                        call.arguments.push_back(parseExpression());

                        if(current().type == Token::Type::RParen) break;

                        expect(Token::Type::Comma);
                    }
                }

                expect(Token::Type::RParen);

                expression = std::move(call);

            }else if(current().type == Token::Type::LBracket){

                consume();

                Expression index = parseExpression();

                expect(Token::Type::RBracket);

                IndexExpression access{};

                access.object = std::make_unique<Expression>(std::move(expression));
                access.index = std::make_unique<Expression>(std::move(index));

                expression = std::move(access);
            
            }else if(current().type == Token::Type::Increment){

                consume();

                if(!std::holds_alternative<VariableExpression>(expression) && !std::holds_alternative<MemberExpression>(expression) && !std::holds_alternative<IndexExpression>(expression)){

                    throw std::runtime_error("Invalid '++' operand at " + std::to_string(position) + " Token: " + current().text);
                }

                PostFixExpression postFix{};

                postFix.operand = std::make_unique<Expression>(std::move(expression));

                postFix.operation = Token::Type::Increment;

                expression = std::move(postFix);

            }else if(current().type == Token::Type::Decrement){

                consume();
                
                if(!std::holds_alternative<VariableExpression>(expression) && !std::holds_alternative<MemberExpression>(expression) && !std::holds_alternative<IndexExpression>(expression)){

                    throw std::runtime_error("Invalid '++' operand at " + std::to_string(position) + " Token: " + current().text);
                }

                PostFixExpression postFix{};

                postFix.operand = std::make_unique<Expression>(std::move(expression));

                postFix.operation = Token::Type::Decrement;

                expression = std::move(postFix);

            }else{

                break;
            }
        }

        return expression;
    }

    Statement Parser::parseStatement(){
        
        switch(current().type){
            
            case Token::Type::Var: return parseVariable();

            case Token::Type::If: return parseIf();

            case Token::Type::Return: return parseReturn();

            default: return parseExpressionStatement();
        }

    }

    Expression Parser::parseExpression(){

        return parseAssignment();
    }

    Definition Parser::parseDefinition(){

        return parseModuleDefinition();
    }

    ModuleImportDefinition Parser::parseImport(){

        expect(Token::Type::Import);

        if(current().type != Token::Type::String && current().type != Token::Type::Identifier){

            throw std::runtime_error("Invalid literal for import path at " + std::to_string(position) + " Token: " + current().text);
        }

        std::string pathOrModule = current().text;

        consume();

        expect(Token::Type::As);

        if(current().type != Token::Type::Identifier){

            throw std::runtime_error("Expected identifier alias at " + std::to_string(position) + " Token: " + current().text);
        }

        std::string alias = current().text;

        consume();

        expect(Token::Type::SemiColon);

        return ModuleImportDefinition{pathOrModule, alias};
    }

    FunctionDefinition Parser::parseFunctionDefinition(){

        FunctionDefinition definition{};

        expect(Token::Type::Define);
        
        if(current().type == Token::Type::Identifier){

            definition.name = current().text;

            consume();

        }else{

            throw std::runtime_error("Expected function name identifier at" + std::to_string(position) + " Token: " + current().text);
        }

        expect(Token::Type::LParen);

        if(current().type != Token::Type::RParen){

            while(true){

                if(current().type != Token::Type::Identifier){

                    throw std::runtime_error("Expected parameter name at" + std::to_string(position) + " Token: " + current().text);
                }

                definition.parameters.push_back(current().text);

                consume();

                if(current().type == Token::Type::RParen) break;

                expect(Token::Type::Comma);
            }
        }
        
        expect(Token::Type::RParen);
        
        expect(Token::Type::Colon);

        while(current().type != Token::Type::EndFunction && current().type != Token::Type::EndOfFile){

            //std::cout << "statement starts with: " << current().text << "\n";
            
            definition.body.push_back(parseStatement());
        }

        expect(Token::Type::EndFunction);

        return definition;

    }

    ModuleDefinition Parser::parseModuleDefinition(){

        ModuleDefinition definition{};
    
        expect(Token::Type::Module);
        
        if(current().type == Token::Type::Identifier){

            definition.name = current().text;

            consume();

        }else{

            throw std::runtime_error("Expected module name identifier at " + std::to_string(position) + " Token: " + current().text);
        }

        expect(Token::Type::Colon);

        while(current().type != Token::Type::EndModule && current().type != Token::Type::EndOfFile){

            switch(current().type){

                case Token::Type::Var:

                    definition.variables.push_back(parseVariable());

                    break;

                case Token::Type::Define:

                    definition.functions.push_back(parseFunctionDefinition());

                    break;

                default: throw std::runtime_error("Expected 'var' or 'fn' inside module at " +std::to_string(position) + " Token: " + current().text);
            }
        }

        expect(Token::Type::EndModule);

        return definition;

    }

}