#include<bangtal.h>

#define up 0
#define down 1
#define right 2
#define left 3

SceneID scene1, nowStage[5];
ObjectID object1, obstacle[8], check[5], startButton;
TimerID timer1, timer2;

int obsX[6], obsY[6], countObst = 0;
int obX, obY, count, moveArrow, stage = 1;
int chX[5], chY[5], point = 0;
bool move = false, rightMove, upMove;
bool checkpointGet[5] = { 0, 0, 0, 0, 0 };

void locateObject_(ObjectID object, SceneID scene, int x, int y, bool shown) {
	locateObject(object, scene, x, y);

	if (shown) showObject(object);
	else if (shown == false) hideObject(object);
}

void checkpoint() {
	for (int i = 0; i < 5; i++) {
		if (!checkpointGet[i] && obX > chX[i] - 40 && obX <= chX[i] + 40 && obY > chY[i] - 40 && obY <= chY[i] + 40) {
			hideObject(check[i]);
			checkpointGet[i] = 1;
			point++;
		}
	}
}

void create() {

	scene1 = createScene("배경", "배경.png");
	nowStage[0] = createScene("맵1", "맵1.png");
	nowStage[1] = createScene("맵1", "맵1.png");
	nowStage[2] = createScene("맵2", "맵2.png");
	nowStage[3] = createScene(".", "맵2.png");

	object1 = createObject("네모.png");
	for (int i = 0; i < 5; i++) check[i] = createObject("포인트.png");

	for (int i = 0; i < 8; i++) obstacle[i] = createObject("장애물.png");

	timer1 = createTimer(0.001f);
	timer2 = createTimer(0.001f);
}

void gameSetting() {
	for (int i = 0; i < 6; i++) {
		hideObject(obstacle[i]);
	}
	if (stage == 1) {

		obX = 120, obY = 360;
		count = 0, countObst = 0;
		move = false;

	}
	else if (stage == 2) {

		obX = 120, obY = 360;
		obsX[0] = 240, obsX[1] = 360, obsX[2] = 480, obsX[3] = 720, obsX[4] = 840, obsX[5] = 960;
		obsY[0] = 260, obsY[1] = 260, obsY[2] = 260, obsY[3] = 260, obsY[4] = 260, obsY[5] = 260;

		chX[0] = 600, chY[0] = 360;
		count = 0, countObst = 0;
		move = false;

		for (int i = 0; i < 6; i++) locateObject_(obstacle[i], nowStage[stage - 1], obsX[i], obsY[i], true);
		locateObject_(check[0], nowStage[stage - 1], chX[0], chY[0], true);

	}
	else if (stage == 3) {


		obX = 600, obY = 80;
		obsX[0] = 320, obsX[1] = 840, obsX[2] = 320, obsX[3] = 840, obsX[4] = 320;
		obsY[0] = 160, obsY[1] = 240, obsY[2] = 320, obsY[3] = 400, obsY[4] = 480;

		chX[1] = 340, chX[2] = 840;
		chY[1] = 180, chY[2] = 500;

		count = 0, countObst = 0;
		move = false;


		for (int i = 1; i < 3; i++) locateObject_(check[i], nowStage[stage - 1], chX[i], chY[i], true);
		for (int i = 0; i < 5; i++) locateObject_(obstacle[i], nowStage[stage - 1], obsX[i], obsY[i], true);
	}

	else if (stage == 4) {

		obX = 600, obY = 80;
		obsX[0] = 320, obsX[1] = 840, obsX[2] = 320, obsX[3] = 840;
		obsY[0] = 500, obsY[1] = 160, obsY[2] = 160, obsY[3] = 500;

		chX[3] = 340, chX[4] = 840;
		chY[3] = 180, chY[4] = 500;

		count = 0, countObst = 0;
		move = false;


		for (int i = 3; i < 5; i++) locateObject_(check[i], nowStage[stage - 1], chX[i], chY[i], true);
		for (int i = 0; i < 4; i++) locateObject_(obstacle[i], nowStage[stage - 1], obsX[i], obsY[i], true);
	}


	locateObject_(object1, nowStage[stage - 1], obX, obY, true);
}

void stopGame() {

	checkpoint();
	if (stage == 1) {
		if (obX >= 1065) {
			stage = 2;
			enterScene(nowStage[stage - 1]);
			gameSetting();
		}
	}
	else if (stage == 2) {
		if (obX >= 1065 && point == 1) {
			stage = 3;
			enterScene(nowStage[stage - 1]);
			gameSetting();
		}

		for (int i = 0; i < 6; i++) {
			if (obX > obsX[i] - 40 && obX < obsX[i] + 40 && obY > obsY[i] - 40 && obY < obsY[i] + 40) {
				obX = 120, obY = 360;
				checkpointGet[0] = 0, point = 0;
				locateObject_(check[0], nowStage[stage - 1], chX[0], chY[0], true);
				locateObject_(object1, nowStage[stage - 1], obX, obY, true);
			}
		}
	}
	else if (stage == 3) {
		if (obY >= 600 && point == 3) {
			stage = 4;
			enterScene(nowStage[stage - 1]);
			gameSetting();
		}

		for (int i = 0; i < 6; i++) {
			if (obX > obsX[i] - 40 && obX < obsX[i] + 40 && obY > obsY[i] - 40 && obY < obsY[i] + 40) {
				obX = 600, obY = 80, point = 1;
				checkpointGet[1] = 0, checkpointGet[2] = 0;
				for (int i = 1; i < 3; i++) locateObject_(check[i], nowStage[stage - 1], chX[i], chY[i], true);
				locateObject_(object1, nowStage[stage - 1], obX, obY, true);
			}
		}
	}
	else if (stage == 4) {
		if (obY >= 600 && point == 5) {
			stage = 1;
			enterScene(scene1);
			locateObject_(startButton, scene1, 528, 100, true);
			showMessage("수고하셨습니다 ~ !");
			gameSetting();
		}

		for (int i = 0; i < 6; i++) {
			if (obX > obsX[i] - 40 && obX < obsX[i] + 40 && obY > obsY[i] - 40 && obY < obsY[i] + 40) {
				obX = 600, obY = 80, point = 3;
				checkpointGet[3] = 0, checkpointGet[4] = 0;
				for (int i = 3; i < 5; i++) locateObject_(check[i], nowStage[stage - 1], chX[i], chY[i], true);
				locateObject_(object1, nowStage[stage - 1], obX, obY, true);
			}
		}
	}
}

void stopMove() {
	if (stage == 1 || stage == 2) {			//스테이지 설정해야됨
		if (obX == 120) rightMove = true;
		else if (obX == 1120) rightMove = false;

		if (obY == 250) upMove = true;
		else if (obY == 480) upMove = false;
	}
	else if (stage == 3 || stage == 4) {
		if (obX == 300 || (obX == 500 && obY >= 80 && obY < 130) || (obX == 500 && obY > 550 && obY <= 600)) rightMove = true;
		else if (obX == 860 || (obX == 660 && obY >= 80 && obY < 130) || (obX == 660 && obY > 550 && obY <= 600)) rightMove = false;

		if (obY == 80 || (obX >= 300 && obX <= 500 && obY == 130) || (obX > 660 && obX <= 900 && obY == 130)) upMove = true;
		else if (obY == 600 || (obX >= 300 && obX <= 500 && obY == 550) || (obX > 660 && obX <= 900 && obY == 550)) upMove = false;
	}
}

void obsXY(bool axis[6][2], int speed, int number) {
	for (int i = 0; i < number; i++) {
		if (axis[i][0] == 0) {
			if (axis[i][1] == 0) obsX[i] += speed;
			else obsX[i] -= speed;
		}
		else {
			if (axis[i][1] == 0) obsY[i] += speed;
			else obsY[i] -= speed;
		}
	}
}

void obsStage(int time, int speed, int number, bool axis[][2]) {

	if (countObst >= 0 && countObst < time) {
		obsXY(axis, speed, number);
		countObst++;
	}
	else if (countObst >= time && countObst < time * 2) {
		for (int i = 0; i < number; i++) {
			axis[i][1] = !axis[i][1];
		}
		obsXY(axis, speed, number);
		countObst++;
	}
	else if (countObst == time * 2) {
		countObst = 0;
	}
}

void obsMove() {

	if (stage == 2) {
		bool axis[6][2] = { {1,0},{1,0},{1,0},{1,0},{1,0},{1,0} };
		obsStage(40, 5, 6, axis);

		for (int i = 0; i < 6; i++) locateObject(obstacle[i], nowStage[stage - 1], obsX[i], obsY[i]);
	}

	else if (stage == 3) {

		bool axis[5][2] = { {0,0},{0,1},{0,0},{0,1}, {0,0} };
		obsStage(50, 10, 5, axis);

		for (int i = 0; i < 5; i++) locateObject(obstacle[i], nowStage[stage - 1], obsX[i], obsY[i]);

	}
	else if (stage == 4) {

		bool axis[4][2] = { {0,0},{0,1},{1,0},{1,1} };
		obsStage(35, 10, 4, axis);

		for (int i = 0; i < 4; i++) locateObject(obstacle[i], nowStage[stage - 1], obsX[i], obsY[i]);

	}
}

void xMove(bool plus) {

	if (count >= 0 && count < 8) {
		if (plus == true && rightMove == true) obX += 5;
		else if (plus == false && rightMove == false) obX -= 5;

		count++;
	}
	else if (count == 8) {
		move = false;
		count = 0;
	}

}

void yMove(bool plus) {

	if (count >= 0 && count < 8) {
		if (plus == true && upMove == true) obY += 5;
		else if (plus == false && upMove == false) obY -= 5;

		count++;
	}
	else if (count == 8) {
		move = false;
		count = 0;
	}
}

void timerCallBack(TimerID timer) {

	if (timer == timer1) {
		stopMove();
		stopGame();

		if (move == true) {
			switch (moveArrow) {
			case up:
				yMove(true);
				break;
			case down:
				yMove(false);
				break;
			case right:
				xMove(true);
				break;
			case left:
				xMove(false);
				break;
			default:
				break;

			}
		}

		locateObject(object1, nowStage[stage - 1], obX, obY);

		setTimer(timer1, 0.01f);
		startTimer(timer1);
	}


	if (timer == timer2) {

		obsMove();

		setTimer(timer2, 0.01f);
		startTimer(timer2);
	}
}

void keyboardCallback(KeyCode key, KeyState state) {

	if (key == KeyCode::KEY_UP_ARROW && state == KeyState::KEY_PRESSED) {
		moveArrow = 0;
		upMove = true;
		move = true;
	}
	else if (key == KeyCode::KEY_DOWN_ARROW && state == KeyState::KEY_PRESSED) {
		moveArrow = 1;
		upMove = false;
		move = true;
	}
	else if (key == KeyCode::KEY_RIGHT_ARROW && state == KeyState::KEY_PRESSED) {
		moveArrow = 2;
		rightMove = true;
		move = true;
	}
	else if (key == KeyCode::KEY_LEFT_ARROW && state == KeyState::KEY_PRESSED) {
		moveArrow = 3;
		rightMove = false;
		move = true;
	}

}

void mouseCallback(ObjectID object, int x, int y, MouseAction action) {
	if (object == startButton) {
		hideObject(startButton);
		startGame(nowStage[stage - 1]);
	}
}

int main() {

	setGameOption(GameOption::GAME_OPTION_INVENTORY_BUTTON, false);
	setGameOption(GameOption::GAME_OPTION_ROOM_TITLE, false);
	setGameOption(GameOption::GAME_OPTION_MESSAGE_BOX_BUTTON, false);

	setKeyboardCallback(keyboardCallback);
	setTimerCallback(timerCallBack);
	setMouseCallback(mouseCallback);

	create();
	gameSetting();

	startTimer(timer1);
	startTimer(timer2);

	startButton = createObject("시작버튼.png");
	locateObject_(startButton, scene1, 528, 100, true);
	startGame(scene1);

}