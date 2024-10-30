input.onButtonPressed(Button.A, function () {
    basic.clearScreen()
})
testrunner.onMlEvent(testrunner.event.NotASpell, function () {
    basic.showString("?")
})
testrunner.onMlEvent(testrunner.event.Flickandwait, function () {
    basic.showString("F")
})
testrunner.onMlEvent(testrunner.event.Waggle, function () {
    basic.showString("W")
})
testrunner.onMlEvent(testrunner.event.Poke, function () {
    basic.showString("P")
})
testrunner.onMlEvent(testrunner.event.Circle, function () {
    basic.showString("C")
})
basic.forever(function () {
	
})
input.onButtonPressed(Button.A, function () {
    basic.showIcon(IconNames.Heart);
})
input.onButtonPressed(Button.B, function () {
    basic.showIcon(IconNames.Yes);
})
