import openai

# Set your OpenAI API key
openai.api_key = 'your-openai-api-key'

# Function to interact with GPT model
def ask_gpt(prompt):
    try:
        # Send request to OpenAI API
        response = openai.Completion.create(
            engine="gpt-4",  # or "gpt-3.5-turbo" if you want
            prompt=prompt,
            max_tokens=150,  # Control the length of the response
            temperature=0.7,  # Higher values make the output more random/creative
            top_p=1,  # Control diversity via nucleus sampling
            n=1,  # Number of completions to generate for the prompt
            stop=None  # Stop at certain token(s) if needed
        )
        # Extract and return the GPT-generated response
        return response.choices[0].text.strip()
    except Exception as e:
        return f"Error: {str(e)}"

# Main function to run the chatbot
def chatbot():
    print("Welcome to the GPT-based Chatbot! Type 'exit' to end the conversation.")
    
    while True:
        user_input = input("You: ")
        
        # Exit condition
        if user_input.lower() == "exit":
            print("Chatbot: Goodbye!")
            break
        
        # Generate response using OpenAI GPT
        response = ask_gpt(user_input)
        print(f"Chatbot: {response}")

# Run the chatbot
if __name__ == "__main__":
    chatbot()
