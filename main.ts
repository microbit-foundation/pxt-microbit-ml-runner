input.onButtonPressed(Button.A, function () {
    basic.clearScreen()
})
testrunner.onMlEvent(testrunner.event.Unknown, function () {
    basic.clearScreen()
})
testrunner.onMlEvent(testrunner.event.Shake, function () {
    basic.showString("S")
})
testrunner.onMlEvent(testrunner.event.Still, function () {
    basic.showIcon(IconNames.Asleep)
})
testrunner.onMlEvent(testrunner.event.Circle, function () {
    basic.showString("C")
})
basic.forever(function () {
    
})
