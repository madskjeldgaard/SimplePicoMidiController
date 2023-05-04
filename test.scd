(
var synthsPlaying = 128.collect({|i| nil});
var noteNum = 60;
var midiChan = 0;

// Connect all input devices
MIDIIn.connectAll;

s.waitForBoot{

    // Set up a MIDIFunc to respond to note on and note off messages
    MIDIFunc.noteOn({|velocity|
        ("Note on received for note number " ++ noteNum).postln;
        synthsPlaying[noteNum] = Synth(\default, [\freq, noteNum.midicps]);
    }, noteNum:noteNum, chan:midiChan);

    MIDIFunc.noteOff({|velocity|
        ("Note off received for note number " ++ noteNum).postln;
        synthsPlaying[noteNum].release;
    }, noteNum:noteNum, chan:midiChan);

}
)
