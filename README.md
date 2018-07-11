<p><b>calib-mpo</b></p>
<p><b>3D stereo camera calibration with QT and openCV, using stereo pairs (PNG, TIF, JPG) or stereo MPO images</b></p>
<br/>

<p>v1 2018-07-10</p>
<br/>

<p>The present code is under GPL v3 license, that means you can do almost whatever you want
with it!</p>
<p>I used bits of code from several sources, mainly from the openCV examples</p>
<br/>

<p><b>*** WHY?</b></p>
<br/>

<p>I didn't find any simple tool (understand: GUI) to calibrate my lens for stereo photography, because my camera produces MPO files. So why not writing it myself ?</p>
<p>I'm not an ace of C++ and QT, in fact I only started using them some month ago. So, if you don't find my code pretty never mind, because it WORKS, and that's all I'm asking of it :)</p>
<br/>

<p><b>*** WITH WHAT?</b></p>
<br/>

<p>Developed using:</p>
<ul>
	<li/>
<p>Linux: Ubuntu
	16.04</p>
	<li/>
<p>QT Creator
	3.5.1</p>
	<li/>
<p>QT 5.5.1</p>
	<li/>
<p>openCV 3.4.1</p>
</ul>

<p>This software should also work under Microsoft Windows: if you tried it successfully please contact me.</p>
<br/>

<p></><b>*** HOW?</b></p>
<br/>

<p> You must first take pictures of checkerboards or circle grids like explained here : https://docs.opencv.org/3.4.1/d4/d94/tutorial_camera_calibration.html</p>
<br/>

<p>How to use the software:</p>
<ul>
	<li/>
<p>Select the type of board (openCV-type) you photographed: checkerboard, symmetric or asymmetric circles</p>
	<ul>
		<li/>
<p>Checkerboard:</p>
		<ul>
			<li/>
<p>enter the number of inner corners: H x V where H  is the number of columns	and V the number of rows</p>
			<li/>
<p>enter the size (in millimeters) of the side length of the squares</p>
		</ul>
		<li/>
<p>Symmetric circles:</p>
		<ul>
			<li/>
<p>enter the number of circles: H x V where H  is the number of circles per columns and V the number of rows</p>
			<li/>
<p>enter the size (in millimeters) of the circles diameter</p>
		</ul>
		<li/>
<p>Asymmetric circles:</p>
		<ul>
			<li/>
<p>enter the number of circles: H x V where H  is the number of circles per columns (it is the same one every row, even if they are shifted) and V the number of rows</p>
			<li/>
<p>enter the size (in millimeters) of the circles diameter</p>
		</ul>
	</ul>
	<li/>
<p>Enter your camera’s sensor size (in millimeters)</p>
	<li/>
<p>Select whether your images are in MPO format or not. openCV accepts many image types like JGP, PNG, TIF…</p>
	<ul>
		<li/>
<p>Your MPO images must contain two jpegs, forming a stereo pair</p>
		<li/>
<p>If not using MPO, this is how it works:</p>
		<ul>
			<li/>
<p>provide 2 files for each stereo pair</p>
			<li/>
<p>the pair is composed of 2 separate images: first file = LEFT, second file = RIGHT</p>
			<li/>
<p>of course the total number of files must be EVEN</p>
		</ul>
	</ul>
	<li/>
<p>Click on the CALIBRATE button:</p>
	<ul>
		<li/>
<p>Select several image files (with  &lt;SHIFT&gt; and &lt;CTRL&gt;)</p>
		<li/>
<p>The stereo pairs are displayed and processed. If the patterns (checkerboard or circles) are found, they are drawn over the original image</p>
		<li/>
<p> There are indicators during this first part: 
		</p>
		<ul>
			<li/>
<p>the blue progress bar represents the overall progress</p>
			<li/>
<p>the red one shows the images that didn’t match the pattern (the red LED indicator also shows that information)</p>
			<li/>
<p>the green LED indicator shows the successful patterns found in stereo pairs</p>
		</ul>
		<li/>
<p>When the overall progress bar reaches 100%, be patient: your camera lens parameters are being computed – it can take a long time, depending on your computer CPUs and the number of successful image pairs (for good results, at least 30 for checkerboards and 15 for circles)</p>
		<li/>
<p>When the parameters are found:</p>
		<ul>
			<li/>
<p>a message shows the average errors found for the images, for the left and right lens, AND the stereo pairs</p>
			<li/>
<p>you will be asked a folder location where you will save the lens parameters, in openCV format (XML and YAML). 3 files will be created: calibration-left, calibration-right and calibration-stereo.xml</p>
		</ul>
	</ul>
</ul>
<br/>

<p>The resulting XML files produced by the software will be useful when you want to rectify stereo pairs before computing a depthmap, or find extrinsic values from them. But this is another software to come soon.</p>
<br/>

<p>Enjoy!</p>
<br/>

<p>AbsurdePhoton.</p>
<p>My photographer website ''Photongénique'': www.absurdephoton.fr</p>
