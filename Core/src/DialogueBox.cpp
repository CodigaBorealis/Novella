#include "../Novella/Components/Gameplay/DialogueBox.hpp"
#include <stdexcept>
#include <string>

namespace Novella::Gameplay{

    void DialogueBox::setBackground(std::shared_ptr<Texture> texture){

        background.setTexture(texture);
    }
    
    void DialogueBox::setPortrait(std::shared_ptr<Texture> texture){

        portrait.setTexture(texture);
    }
    
    void DialogueBox::setSpeaker(const std::string& name){

        speaker.setText(name);
    }
    
    void DialogueBox::setDialogue(size_t index){

        if(index >= lines.size()) throw std::runtime_error("Cannot set dialogue to line '" + std::to_string(index) + "' because lines only has size '" + std::to_string(lines.size()) + "'");

        currentIndex = index;

        const auto& line = lines[index];
        
        speaker.setText(line.speaker);
        text.setText(lines[index].text);
    }
    
    void DialogueBox::setFont(std::shared_ptr<Font> font){

        text.setFont(font);
    }
    
    void DialogueBox::setDialogueLines(std::vector<DialogueLine> lines){

        this->lines = std::move(lines);

        currentIndex = 0;

        if(this->lines.empty()){
            
            clear();

            return;
        }

        text.setText(this->lines.front().text);
    }
    
    void DialogueBox::nextLine(){

        if(!hasNext()) return;

        currentIndex ++;

        setDialogue(currentIndex);
    }
    
    void DialogueBox::previousLine(){

        if(currentIndex == 0) return;

        currentIndex --;

        setDialogue(currentIndex);
    }
    
    bool DialogueBox::hasNext() const{

        return !lines.empty() && currentIndex + 1 < lines.size();

    }
    
    void DialogueBox::clear(){

        text.setText("");
    }
    
    void DialogueBox::reset(){

        currentIndex = 0;

        if(lines.empty()){
            
            clear();

            return;
        }

        setDialogue(0);
    }
    
    const DialogueBox::DialogueLine& DialogueBox::currentLine() const{

        if(lines.empty()) throw std::runtime_error("Cannot call currentLine() because lines is empty");

        return lines[currentIndex];
    }
    
}