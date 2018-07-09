<p style="margin-bottom: 0in; line-height: 100%"><b>calib-mpo</b></p>
<p style="margin-bottom: 0in; line-height: 100%"><b>Stereo camera
calibration with QT and openCV, using stereo pairs (PNG, TIF, JPG) or
stereo MPO images</b></p>
<p style="margin-bottom: 0in; line-height: 100%"><br/>

</p>
<p style="margin-bottom: 0in; line-height: 100%">2018-07-10</p>
<p style="margin-bottom: 0in; line-height: 100%"><br/>

</p>
<p style="margin-bottom: 0in; line-height: 100%">The present code is
under GPL v3 license, that means you can do almost whatever you want
with it!</p>
<p style="margin-bottom: 0in; line-height: 100%"><br/>

</p>
<p style="margin-bottom: 0in; line-height: 100%"><b>*** WHY?</b></p>
<p style="margin-bottom: 0in; line-height: 100%"><br/>

</p>
<p style="margin-bottom: 0in; line-height: 100%">I didn't find any
simple tool (understand: GUI) to calibrate my lens for stereo
photography. So why not writing it myself ?</p>
<p style="margin-bottom: 0in; line-height: 100%">I'm not an ace of
C++ and QT, in fact I only started using them some month ago. So, if
you don't find my code pretty never mind, because it WORKS, and
that's all I'm asking of it :)</p>
<p style="margin-bottom: 0in; line-height: 100%"><br/>

</p>
<p style="margin-bottom: 0in; line-height: 100%"><b>*** WITH WHAT?</b></p>
<p style="margin-bottom: 0in; line-height: 100%"><br/>

</p>
<p style="margin-bottom: 0in; line-height: 100%">Developed using:</p>
<ul>
	<li/>
<p style="margin-bottom: 0in; line-height: 100%">Linux: Ubuntu
	16.04</p>
	<li/>
<p style="margin-bottom: 0in; line-height: 100%">QT Creator
	3.5.1</p>
	<li/>
<p style="margin-bottom: 0in; line-height: 100%">QT 5.5.1</p>
	<li/>
<p style="margin-bottom: 0in; line-height: 100%">openCV 3.4.1</p>
</ul>
<p style="margin-bottom: 0in; line-height: 100%"><br/>

</p>
<p style="margin-bottom: 0in; line-height: 100%"></>*** HOW?</b></p>
<p style="margin-bottom: 0in; line-height: 100%"><br/>

</p>
<p style="margin-bottom: 0in; line-height: 100%">How to use the
software:</p>
<ul>
	<li/>
<p style="margin-bottom: 0in; line-height: 100%">Select the
	type of board (openCV-type) you photographed: checkerboard,
	symmetric or asymmetric circles</p>
	<ul>
		<li/>
<p style="margin-bottom: 0in; line-height: 100%">Checkerboard:</p>
		<ul>
			<li/>
<p style="margin-bottom: 0in; line-height: 100%">enter the
			number of inner corners: H x V where H  is the number of columns
			and V the number of rows</p>
			<li/>
<p style="margin-bottom: 0in; line-height: 100%">enter the
			size (in millimeters) of the side length of the squares</p>
		</ul>
		<li/>
<p style="margin-bottom: 0in; line-height: 100%">Symmetric
		circles:</p>
		<ul>
			<li/>
<p style="margin-bottom: 0in; line-height: 100%">enter the
			number of circles: H x V where H  is the number of circles per
			columns and V the number of rows</p>
			<li/>
<p style="margin-bottom: 0in; line-height: 100%">enter the
			size (in millimeters) of the circles diameter</p>
		</ul>
		<li/>
<p style="margin-bottom: 0in; line-height: 100%">Asymmetric
		circles:</p>
		<ul>
			<li/>
<p style="margin-bottom: 0in; line-height: 100%">enter the
			number of circles: H x V where H  is the number of circles per
			columns (it is the same one every row, even if they are shifted)
			and V the number of rows</p>
			<li/>
<p style="margin-bottom: 0in; line-height: 100%">enter the
			size (in millimeters) of the circles diameter</p>
		</ul>
	</ul>
	<li/>
<p style="margin-bottom: 0in; line-height: 100%">Enter your
	camera’s sensor size (in millimeters)</p>
	<li/>
<p style="margin-bottom: 0in; line-height: 100%">Select wether
	your images are in MPO format or not. openCV accepts many image
	types like JGP, PNG, TIF…</p>
	<ul>
		<li/>
<p style="margin-bottom: 0in; line-height: 100%">Your MPO
		images must contain two jpegs, forming a stereo pair</p>
		<li/>
<p style="margin-bottom: 0in; line-height: 100%">If not using
		MPO, this is how it works:</p>
		<ul>
			<li/>
<p style="margin-bottom: 0in; line-height: 100%">provide 2
			files for each stereo pair</p>
			<li/>
<p style="margin-bottom: 0in; line-height: 100%">the pair is
			composed of 2 separate images: first file = LEFT, second file =
			RIGHT</p>
			<li/>
<p style="margin-bottom: 0in; line-height: 100%">of course
			the total number of files must be EVEN</p>
		</ul>
	</ul>
	<li/>
<p style="margin-bottom: 0in; line-height: 100%">Click on the
	CALIBRATE button:</p>
	<ul>
		<li/>
<p style="margin-bottom: 0in; line-height: 100%">Select
		several image files (with  &lt;SHIFT&gt; and &lt;CTRL&gt;)</p>
		<li/>
<p style="margin-bottom: 0in; line-height: 100%">The stereo
		pairs are displayed and processed. If the patterns (checkerboard or
		circles) are found, they are drawn over the original image</p>
		<li/>
<p style="margin-bottom: 0in; line-height: 100%"> There are
		indicators during this first part: 
		</p>
		<ul>
			<li/>
<p style="margin-bottom: 0in; line-height: 100%">the blue
			progress bar represents the overall progress</p>
			<li/>
<p style="margin-bottom: 0in; line-height: 100%">the red one
			shows the images that didn’t match the pattern (the red LED
			indicator also shows that information)</p>
			<li/>
<p style="margin-bottom: 0in; line-height: 100%">the green
			LED indicator shows the successful patterns found in stereo pairs</p>
		</ul>
		<li/>
<p style="margin-bottom: 0in; line-height: 100%">When the
		overall progress bar reaches 100%, be patient: your camera
		parameters are being computed – it can take a long time,
		depending on your computer CPUs and the number of successful image
		pairs (for good results, at least 30 for checkerboards and 15 for
		circles)</p>
		<li/>
<p style="margin-bottom: 0in; line-height: 100%">When the
		parameters are found:</p>
		<ul>
			<li/>
<p style="margin-bottom: 0in; line-height: 100%">a message
			shows the average errors found for the images, for the left and
			right lens, AND the stereo pairs</p>
			<li/>
<p style="margin-bottom: 0in; line-height: 100%">you will be
			asked a folder location where you will save the lens parameters,
			in openCV format (XML and YAML). 3 files will be created:
			calibration-left, calibration-right and calibration-stereo.xml</p>
		</ul>
	</ul>
</ul>
<p style="margin-bottom: 0in; line-height: 100%"><br/>

</p>
<p style="margin-bottom: 0in; line-height: 100%">The resulting XML
files produced by the software will be useful when you want to
rectify stereo pairs before computing a depthmap, or find extrinsic
values from them. But this is another software to come soon.</p>
<p style="margin-bottom: 0in; line-height: 100%"><br/>

</p>
<p style="margin-bottom: 0in; line-height: 100%">Enjoy!</p>
<p style="margin-bottom: 0in; line-height: 100%"><br/>

</p>
<p style="margin-bottom: 0in; line-height: 100%">AbsurdePhoton.</p>
</body>
</html>
