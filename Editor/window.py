import customtkinter as ctk
ctk.set_appearance_mode("Dark")
ctk.set_default_color_theme("blue") 

class App(ctk.CTk):

    def __init__(self):

        super().__init__()

        self.title("Novella Editor")

        self.geometry("1280x720")

        self.label = ctk.CTkLabel(self, text="Hello world", font=ctk.CTkFont(size=20, weight="bold"))

        self.label.pack(padx=20, pady=40)
        
        self.btn = ctk.CTkButton(self, text="Click Me", command=self.button_click)

        self.btn.pack(padx=20, pady=10)

    def button_click(self):

        print("Button was pressed!")

if __name__ == "__main__":

    app = App()
    
    app.mainloop()