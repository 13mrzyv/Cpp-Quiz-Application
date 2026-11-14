#include <iostream>
#include <string>	
#include <vector>
#include <algorithm>
#include <random>
#include <numeric>

using namespace std;

class Question {
public:
	string questionText;
	vector<string> options;
	int correctOptionIndex;
	Question(string text, vector<string> opts, int correctIndex) {
		questionText = text;
		options = opts;
		correctOptionIndex = correctIndex;
	}
	Question() {
		questionText = "";
		options = {};
		correctOptionIndex = 0;
	}
	void getQuestion() {
		cout << questionText << endl;
		for (int i = 0; i < options.size(); i++) {
			cout << i + 1 << ". " << options[i] << endl;
		}
	}
	int getCorrectOptionIndex() {
		return correctOptionIndex;
	}
};

class Quiz {
public:
	string quizName;
	vector<Question> questions;
	void addQuestion(Question q) {
		questions.push_back(q);
	}


	void startQuiz() {
		if (questions.empty()) {
			cout << "This quiz has no questions!\n";
			return;
		}

		random_device rd;
		mt19937 rng(rd());

		vector<Question> randomQuestions = questions;
		shuffle(randomQuestions.begin(), randomQuestions.end(), rng);

		for (Question& question : randomQuestions) {

			int correctIndex = question.correctOptionIndex;
			string correctAnswer = question.options[correctIndex];

			shuffle(question.options.begin(),
				question.options.end(), rng);

			for (int i = 0; i < question.options.size(); i++) {
				if (question.options[i] == correctAnswer) {
					question.correctOptionIndex = i;
					break;
				}
			}
		}

		int currentIndex = 0;

		vector<int> userAnswers(randomQuestions.size(), -1);

		while (true) {
			cout << "\n========== QUIZ ==========\n";

			cout << "Question " << currentIndex + 1
				<< "/" << randomQuestions.size() << endl;

			randomQuestions[currentIndex].getQuestion();

			if (userAnswers[currentIndex] != -1) {
				cout << "Your previous answer: "
					<< userAnswers[currentIndex] + 1 << endl;
			}

			cout << "\nEnter answer (1-"
				<< randomQuestions[currentIndex].options.size()
				<< "), or 0 to keep current answer: ";

			int answer;
			cin >> answer;

			if (!cin) {
				cin.clear();
				cin.ignore(10000, '\n');
				cout << "Please enter a number!\n";
				continue;
			}

			if (answer >= 1 &&
				answer <= static_cast<int>(
					randomQuestions[currentIndex].options.size())) {

				userAnswers[currentIndex] = answer - 1;
			}
			else if (answer != 0) {
				cout << "Invalid answer!\n";
				continue;
			}

			cout << "\n1. Previous\n";
			cout << "2. Next\n";
			cout << "3. Submit\n";

			cout << "Select: ";

			int choice;
			cin >> choice;

			if (!cin) {
				cin.clear();
				cin.ignore(10000, '\n');
				cout << "Invalid choice!\n";
				continue;
			}

			switch (choice) {
			case 1:
				if (currentIndex > 0) {
					currentIndex--;
				}
				else {
					cout << "This is the first question!\n";
				}
				break;

			case 2:
				if (currentIndex <
					static_cast<int>(randomQuestions.size()) - 1) {
					currentIndex++;
				}
				else {
					cout << "This is the last question!\n";
				}
				break;

			case 3: {
				int correct = 0;
				int incorrect = 0;

				for (int i = 0; i < randomQuestions.size(); i++) {
					if (userAnswers[i] == -1) {
						continue;
					}

					if (userAnswers[i] ==
						randomQuestions[i].correctOptionIndex) {
						correct++;
					}
					else {
						incorrect++;
					}
				}

				cout << "\n========== RESULT ==========\n";
				cout << "Correct: " << correct << endl;
				cout << "Incorrect: " << incorrect << endl;
				cout << "Total questions: "
					<< randomQuestions.size() << endl;

				return;
			}

			default:
				cout << "Invalid choice!\n";
			}
		}
	}


};



class QuizManager {
public:
	vector<Quiz> quizzes;
	void welcome(string role) {
		cout << "Welcome to the Quiz, " << role << "!" << endl;
		if (role == "admin") {
			Quiz quiz;
			addQuiz(quiz);
		}
		else if (role == "user") {
			cout << "You can take quizzes." << endl;
			if (quizzes.empty()) {
				cout << "No quizzes available!" << endl;
				return;
			}
			showQuizzes();
			int choice;
			cout << "Select quiz: ";
			cin >> choice;

			takeQuiz(choice - 1);
		}
		else {
			cout << "Invalid role. Please enter 'admin' or 'user'." << endl;
		}
	}
	void takeQuiz(int index) {
		if (index < 0 || index >= quizzes.size()) {
			cout << "Invalid quiz index." << endl;
			return;
		}
		quizzes.at(index).startQuiz();
	}
	void addQuiz(Quiz quiz) {
		cout << "Enter quiz name: ";
		cin >> quiz.quizName;

		cout << "Lets add questions." << endl;
		
		while (true) {
			Question question;
			cout << "Enter a question (or type 'exit' to finish): ";
			getline(cin >> ws, question.questionText);
			if (question.questionText == "exit") {
				break;
			}
			cout << "Enter the number of options: ";
			int numOptions;
			cin >> numOptions;
			question.options.resize(numOptions);
			for (int i = 0; i < numOptions; i++) {
				cout << "Enter option " << i + 1 << ": ";
				getline(cin >> ws, question.options[i]);
			}
			cout << "Enter the index of the correct option (1-" << numOptions << "): ";
			cin >> question.correctOptionIndex;
			question.correctOptionIndex--;

			quiz.addQuestion(question);
		}
		quizzes.push_back(quiz);
	}
	void showQuizzes() {
		for (int i = 0; i < quizzes.size(); i++) {
			cout << i + 1 << ". "
				<< quizzes[i].quizName << endl;
		}
	}

	void showMenu(string role) {
		int choice;

		while (true) {
			cout << "\n===== QUIZ MENU =====\n";
			if (role == "admin") {
				cout << "1. Create Quiz\n";
			}
			cout << "2. Start Quiz\n";
			cout << "0. Exit\n";
			cout << "Select: ";
			cin >> choice;
			switch (choice) {
			case 1:
				if (role == "admin") {
					Quiz quiz;
					addQuiz(quiz);
				}
				else {
					cout << "Access denied!\n";
				}
				break;

			case 2:
				if (quizzes.empty()) {
					cout << "No quizzes available!\n";
					break;
				}
				showQuizzes();

				int index;
				cout << "Select quiz: ";
				cin >> index;

				takeQuiz(index - 1);
				break;

			case 0:
				cout << "Goodbye!\n";
				return;

			default:
				cout << "Invalid choice!\n";
			}
		}
	}
};


void main() {
	QuizManager manager;

	string role;

	cout << "Enter your role (admin/user): ";
	cin >> role;

	if (role != "admin" && role != "user") {
		cout << "Invalid role!\n";
		return;
	}
	manager.showMenu(role);
}