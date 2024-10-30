testrunner.onMlEvent(testrunner.event.Walking, function () {
    basic.showString("W")
})
testrunner.onMlEvent(testrunner.event.JumpingUpdown, function () {
    basic.showString("J")
})
testrunner.onMlEvent(testrunner.event.BeingStill, function () {
    basic.showString("S")
})
basic.forever(function () {
	
})
input.onButtonPressed(Button.A, function () {
    basic.showIcon(IconNames.Heart);
})
input.onButtonPressed(Button.B, function () {
    basic.showIcon(IconNames.Yes);
})
