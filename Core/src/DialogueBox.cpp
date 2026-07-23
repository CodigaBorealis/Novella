#include "../Novella/Components/Gameplay/DialogueBox.hpp"
#include <stdexcept>
#include <string>
#include "../Novella/Systems/Resources/ResourceManager.hpp"

namespace Novella::Gameplay{
    
    void DialogueBox::applyCurrentDialogue(const ResourceManager& resourceManger){

        if(!lines[currentIndex].backgroundID.empty() && background.has_value()){

            background->setTexture(resourceManger.getTexture(lines[currentIndex].backgroundID));
        }

        if(!lines[currentIndex].textFontID.empty() && text.has_value()){

            text->setFont(resourceManger.getFont(lines[currentIndex].textFontID));
        }   

        if(!lines[currentIndex].speakerFontID.empty() && text.has_value()){

            speaker->setFont(resourceManger.getFont(lines[currentIndex].speakerFontID));
        }   

        if(!lines[currentIndex].portraitID.empty() && text.has_value()){

            portrait->setTexture(resourceManger.getTexture(lines[currentIndex].portraitID));
        }

        if(!lines[currentIndex].voiceClipID.empty()){

            voiceClip = lines[currentIndex].voiceClipID;
        }

        if(!lines[currentIndex].speaker.empty()){

            
        }
    }

    void DialogueBox::setDialogue(size_t index){

        if(index >= lines.size()) throw std::runtime_error("Cannot set dialogue to line '" + std::to_string(index) + "' because lines only has size '" + std::to_string(lines.size()) + "'");

        currentIndex = index;

        const auto& line = lines[index];
        
        speaker->setText(line.speaker);
        text->setText(lines[index].text);
    }
    
    void DialogueBox::setDialogueLines(std::vector<DialogueLine> lines){

        this->lines = std::move(lines);

        currentIndex = 0;

        if(this->lines.empty()){
            
            clear();

            return;
        }

        text->setText(this->lines.front().text);
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

        text->setText("");
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