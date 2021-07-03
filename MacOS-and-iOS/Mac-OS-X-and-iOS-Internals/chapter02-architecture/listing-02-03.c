// Listing 2-3: Demonstrating a very simple (partial) implementation of the say(1) utility

#include <ApplicationServices/ApplicationServices.h>
// Quick and dirty (partial) implementation of OS X's say(1) command
// Compile with -framework ApplicationServices
void main (int argc, char **argv) {
    OSErr rc;
    SpeechChannel channel;
    VoiceSpec vs;
    int voice;
    char *text = "What do you want me to say?";
    if (!argv[1]) { 
        voice = 1; 
    } 
    else { 
        voice = atoi(argv[1]); 
    }
    if (argc == 3) { 
        text = argv[2]; 
    }
    // GetIndVoice gets the voice defined by the (positive) index
    rc= GetIndVoice(voice, // SInt16       index,
                    &vs);  // VoiceSpec *  voice)
    // NewSpeechChannel basically makes the voice usable
    rc = NewSpeechChannel(&vs,// VoiceSpec * voice, /* can be NULL */
                          &channel);
    // And SpeakText... speaks!
    rc = SpeakText(channel,      // SpeechChannel   chan,
                  text,          // const void *    textBuf,
                  strlen(text)); //unsigned long   textBytes)
    
    if (rc) { 
        fprintf (stderr,"Unable to speak!\n"); 
        exit(1);
    }

    // Because speech is asynchronous, wait until we are done.
    // Objective-C has much nicer callbacks for this.
    while (SpeechBusy()) 
        sleep(1);
    exit(0);
}