#include <iostream>
#include <cstdlib>

#include <string> 

using namespace std;
enum enWinner { Winner = 1, Loser = 2 };
enum enOperationType { Add = 1, Sub = 2, Mul = 3, Div = 4, OpMix = 5 };
enum enQuestionLevel { Easy = 1, Medium = 2, Hard = 3, LevelMix = 4 };

struct stInputInfo
{
	int Number1, Number2, PlayerAnswer, RightAnswer;
	enWinner Winner;
	enQuestionLevel QuestionLevel;
	enOperationType OperationType,MixOperationType;
	string OperationSymbol;
};
struct stGameInfo
{
	int HowManyQuestions, RightAnswers, WrongAnswers;
	string OperationSymbol, QuestionLevel;
	enWinner Winner;
};
int RandomNumber(int From, int To)
{
	int RandomNumber;
	RandomNumber = rand() % (To - From + 1) + From;
	return RandomNumber;
}
void SetWinnerScreenColor(enWinner Winner)
{
	switch (Winner)
	{
	case enWinner::Winner:
		system("color 2F");
		break;
	case enWinner::Loser:
		system("color 4F");
		cout << "\a";
		break;
	default:
		system("color 0F");
		break;
	}
}
int ReadHowManyQuestions()
{
	int HowManyQuestions = 1;
	do
	{
		cout << "How many questions do you want to answer? ";
		cin >> HowManyQuestions;
	} while (HowManyQuestions <= 0);
	return HowManyQuestions;
}

enOperationType ReadOperationType()
{
	int Number;
	cout << "Enter operation type [1] Add, [2] Sub, [3] Mul, [4] Div, [5] Mix. ";
	cin >> Number;
	return enOperationType(Number);
}

enQuestionLevel ReadQuestionLevel()
{
	int Number;
	cout << "Enter question level [1] Easy, [2] Medium, [3] Hard, [4] Mix. ";
	cin >> Number;
	return enQuestionLevel(Number);
}
enOperationType GetMixOperationType(enOperationType OperationType)
{
	if (OperationType == enOperationType::OpMix)
		return enOperationType(RandomNumber(1, 4));
	else
		return OperationType;
}
enQuestionLevel GetMixQuestionLevel(enQuestionLevel QuestionLevel)
{
	if (QuestionLevel == enQuestionLevel::LevelMix)
		return enQuestionLevel(RandomNumber(1, 3));
	else
		return QuestionLevel;
}

string GetOperationSymbol(enOperationType OperationType)
{
	switch (OperationType)
	{
	case enOperationType::Add:
		return "+";
		break;
	case enOperationType::Sub:
		return "-";
		break;
	case enOperationType::Mul:
		return "*";
		break;
	case enOperationType::Div:
		return "/";
		break;
	default:
		return "+";
		break;
	}
}

void GetQuestionNumbers(int& Number1, int& Number2 ,enQuestionLevel QuestionLevel)
{
	switch (QuestionLevel)
	{
	case enQuestionLevel::Easy:
		Number1 = RandomNumber(1, 9);
		Number2 = RandomNumber(1, 9);
		break;
	case enQuestionLevel::Medium:
		Number1 = RandomNumber(10, 49);
		Number2 = RandomNumber(10, 49);
		break;
	case enQuestionLevel::Hard:
		Number1 = RandomNumber(50, 100);
		Number2 = RandomNumber(50, 100);
		break;
	}
}



string GetQuestionLevelName(enQuestionLevel QuestionLevel)
{
	switch (QuestionLevel)
	{
	case enQuestionLevel::Easy:
		return "Easy";
		break;
	case enQuestionLevel::Medium:
		return "Medium";
		break;
	case enQuestionLevel::Hard:
		return "Hard";
		break;
	default:
		return "Mix";
		break;
	}
}

int GetRightAnswer(stInputInfo InputInfo)
{
	switch (InputInfo.MixOperationType)
	{
	case enOperationType::Add:
		return (InputInfo.Number1 + InputInfo.Number2);
		break;
	case enOperationType::Sub:
		return (InputInfo.Number1 - InputInfo.Number2);
		break;
	case enOperationType::Mul:
		return (InputInfo.Number1 * InputInfo.Number2);
		break;
	case enOperationType::Div:
		return (InputInfo.Number1 / InputInfo.Number2);
		break;
	default:
		return (InputInfo.Number1 + InputInfo.Number2);
		break;
	}
}

void PrintQuestion(stInputInfo InputInfo)
{
	cout << InputInfo.Number1 << endl;
	cout << InputInfo.Number2 << " " << InputInfo.OperationSymbol << endl;
	cout << "____________________\n";
}

int ReadPlayerAnswer()
{
	int PlayerAnswer;
	cin >> PlayerAnswer;
	return PlayerAnswer;
}

enWinner CheckPlayerAnswer(int PlayerAnswer,int RightAnswer)
{
	if (PlayerAnswer == RightAnswer)
		return enWinner::Winner;
	else
		return enWinner::Loser;
}

void PrintQuestionResult(stInputInfo InputInfo)
{
	switch (InputInfo.Winner)
	{
	case enWinner::Loser:
		cout << "Wrong Answer :-(\nThe right answer is: " << InputInfo.RightAnswer << endl;
		break;
	default:
		cout << "Right Answer :-)\n";
		break;
	}
	SetWinnerScreenColor(InputInfo.Winner);
}


void CountAnswers(int& RightAnswers, int& WrongAnswers, enWinner Winner)
{
	if (Winner == enWinner::Winner)
		++RightAnswers;
	else
		++WrongAnswers;
}

enWinner CheckGameWinner(int RightAnswers, int WrongAnswers)
{
	if (RightAnswers >= WrongAnswers)
		return enWinner::Winner;
	else
		return enWinner::Loser;
}


stGameInfo FillGameInfo(int HowManyQuestions, int RightAnswers, int WrongAnswers,enOperationType OperationType, enQuestionLevel QuestionLevel)
{
	stGameInfo GameInfo;
	GameInfo.HowManyQuestions = HowManyQuestions;
	GameInfo.RightAnswers = RightAnswers;
	GameInfo.WrongAnswers = WrongAnswers;
	GameInfo.QuestionLevel = GetQuestionLevelName(QuestionLevel);
	GameInfo.OperationSymbol = GetOperationSymbol(OperationType);
	GameInfo.Winner = CheckGameWinner(RightAnswers, WrongAnswers);
	return GameInfo;

}

stGameInfo PlayGame()
{
	stInputInfo InputInfo;
	stGameInfo GameInfo;
	int RightAnswers = 0, WrongAnswers = 0;
	int HowManyQuestions = ReadHowManyQuestions();
	InputInfo.QuestionLevel = ReadQuestionLevel();
	InputInfo.OperationType = ReadOperationType();
	for (int QuestionNumber = 1;QuestionNumber <= HowManyQuestions;QuestionNumber++)
	{
		
		GetQuestionNumbers(InputInfo.Number1, InputInfo.Number2, GetMixQuestionLevel(InputInfo.QuestionLevel));
		InputInfo.MixOperationType = GetMixOperationType(InputInfo.OperationType);
		InputInfo.OperationSymbol = GetOperationSymbol(InputInfo.MixOperationType);
		InputInfo.RightAnswer = GetRightAnswer(InputInfo);
		PrintQuestion(InputInfo);
		InputInfo.PlayerAnswer = ReadPlayerAnswer();
		InputInfo.Winner = CheckPlayerAnswer(InputInfo.PlayerAnswer, InputInfo.RightAnswer);
		CountAnswers(RightAnswers, WrongAnswers, InputInfo.Winner);
		PrintQuestionResult(InputInfo);
	}
	GameInfo = FillGameInfo(HowManyQuestions, RightAnswers, WrongAnswers, InputInfo.OperationType, InputInfo.QuestionLevel);
	return GameInfo;
}
void PrintFinalResult(stGameInfo GameInfo)
{
	SetWinnerScreenColor(GameInfo.Winner);
	if (GameInfo.Winner == enWinner::Winner)
	{
		cout << "_______________________________\n";
		cout << "Final Result Is PASS :-) \n";
		cout << "_______________________________\n";
	}
	else
	{
		cout << "_______________________________\n";
		cout << "Final Result Is FAIL :-( \n";
		cout << "_______________________________\n";
	}
	cout << "Number Of Questions: " << GameInfo.HowManyQuestions << endl;
	cout << "Question Level: " << GameInfo.QuestionLevel << endl;
	cout << "Operation Type: " << GameInfo.OperationSymbol << endl;
	cout << "Number Of Right Answers: " << GameInfo.RightAnswers << endl;
	cout << "Number Of Wrong Answers: " << GameInfo.WrongAnswers << endl;
	cout << "_______________________________\n";
}
void ResetScreen()
{
	system("cls");
	system("color 0F");
}
void StartGame()
{
	char Choice = 'y';
	do
	{
		ResetScreen();
		PrintFinalResult(PlayGame());
		cout << endl << "Do you want to play again? Y/N ";
		cin >> Choice;
	} while (Choice == 'y' || Choice == 'Y');
}


int main()
{
	srand((unsigned)time(NULL));
	StartGame();
	return 0;
}