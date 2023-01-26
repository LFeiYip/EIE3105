void control(int &left, int &right) 
{
	int count_left; 
	int count_right;
	int error_speed; //count different
	double temp; 

	//target value
	double vTL;
	double vTR;
	double eL;//error between target and test value
	double eR;
	double v=1;

	//PWM value
	int pwmL;
	int pwmR;

	//previous value
	int ep = 0;//previous value of error
	double tempp = 0;
	int pwmLp = 15000;
	int pwmRp = 15000;
	double eLp = 0;
	double eRp = 0;

	count_left = left;
	count_right = right;
	error_speed = count_left - count_right;
	temp = tempp + 0.382*error_speed - 0.409*ep;

	//Dleft[k]= Dleft[k-1] +210.3*e[k]-209.7*e[k-1]
	vTL = v - temp;
	eL = vTL - count_left;
	pwmL = pwmLp + 210.3 * eL - 209.7*eLp;

	//Dright[k]= Dright[k-1] +420.5*e[k]-419.5*e[k-1]
	vTR = v + temp;
	eR = vTR - count_right;
	pwmR = pwmRp + 420.5 * eR - 419.5*eRp;

	int pwm_error = 10000;
	left = pwmL + pwm_error;//modified left wheel in this design
	right = pwmR;

	//end of the loop, save the current value to previous value 
	eLp = eL;
	eRp = eR;
	ep = error_speed;
	tempp = temp;
	pwmLp = pwmL;
	pwmRp = pwmR;
}