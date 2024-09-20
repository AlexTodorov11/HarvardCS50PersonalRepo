import random
import re

# Define a list of responses for various user inputs
responses = {
    "hello": ["Hi there!", "Hello!", "Greetings!", "Hey!"],
    "how are you": ["I'm just a program, but thanks for asking!", "Doing well! How about you?"],
    "what is your name": ["I am an AI chatbot, but you can call me ALYX for short.", "I don't have a name, but I can chat with you!"],
    "goodbye": ["Goodbye!", "See you later!", "Bye! Take care!"],
    "thank you": ["You're welcome!", "Glad I could help!", "No problem!"],
    "default": ["I'm not sure I understand. Can you rephrase?", "Tell me more.", "Interesting!"],
    "what is your fav color": ["Green!", " Green what about yours?"]
}

# Function to preprocess the user input
def preprocess_input(user_input):
    # Lowercase the input and remove punctuation using regex
    user_input = user_input.lower()
    user_input = re.sub(r'[^\w\s]', '', user_input)
    return user_input

# Function to match user input to known patterns and respond accordingly
def get_response(user_input):
    # Preprocess the input
    processed_input = preprocess_input(user_input)

    # Check if any known patterns match
    for key in responses:
        if key in processed_input:
            return random.choice(responses[key])

    # If no match, return a default response
    return random.choice(responses["default"])

# Main function to run the chatbot
def chatbot():
    print("Welcome to the AI Chatbot! Type 'exit' to end the conversation.")

    while True:
        user_input = input("You: ")

        # Exit condition
        if user_input.lower() == "exit":
            print("Chatbot: Goodbye!")
            break

        # Get chatbot response
        response = get_response(user_input)
        print(f"Chatbot: {response}")

# Run the chatbot
if __name__ == "__main__":
    chatbot()
