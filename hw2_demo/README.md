(1) how to setup and run your program<br>

	1. enter the command: ```sudo mbed compile --source . --source ~/ee2405/mbed-os-build/ -m B_L4S5I_IOT01A -t GCC_ARM -f```
	2. push the button (A1 is used to decrease the pre_freq, A3 is used to increase the pre_freq)(note that each change is 10 frequencies.)
	3. push the A2 to confirm the frequency of the wave (then the /dev/ttyACM\* will output the sampled data)
	4. enter the command: ```sudo python3 FFT.py```
	5. the code FFT.py will output a figure which has two subplots
	(Then we can keep repeating the steps 2~5)
	
接下來是用照片展示我大概如何架設板子和連線的<br>
![image](https://github.com/EricChenSudo/hw2/blob/master/hw2_demo/326742.jpg)

![image](https://github.com/EricChenSudo/hw2/blob/master/hw2_demo/326743.jpg)
	   

(2) What are the result<br>

![image](https://github.com/EricChenSudo/hw2/blob/master/hw2_demo/326741.jpg)
pre_freq是正在選擇的頻率<br>
而freq是按下確認鍵後所輸出的頻率<br>
而藍色的bar是用圖形的方式來顯示現在顯示的頻率有多快<br>

![image](https://github.com/EricChenSudo/hw2/blob/master/hw2_demo/Screenshot%20from%202021-03-31%2004-59-06.png)
上圖中的紅線是我們用板板製造出的三角波<br>
而藍色線是通過RC filter後所量到的波<br>

接下來我們去執行FFT.py的python code，也就是上面有說要輸入的command: sudo python3 FFT.py<br>
如此會得到下圖<br>
(note)在上面的圖是the sampled data we get from the filtered wave<br>
(note)在下方的圖是the frequency spectrum of the wave we filtered<br>

![image](https://github.com/EricChenSudo/hw2/blob/master/hw2_demo/Screenshot%20from%202021-03-31%2003-11-37.png)
上圖是按下200赫茲confirm後，且執行FFT.py的輸出結果<br>

![image](https://github.com/EricChenSudo/hw2/blob/master/hw2_demo/Screenshot%20from%202021-03-31%2003-12-51.png)
上圖是按下100赫茲confirm後，且執行FFT.py的輸出結果<br>
	
