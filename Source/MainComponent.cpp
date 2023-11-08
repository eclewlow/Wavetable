#include <JuceHeader.h>
#include "MainComponent.h"
#include "Display.h"
#include "Globals.h"

//==============================================================================
MainComponent::MainComponent()
{
    // Make sure you set the size of the component after
    // you add any child components.
    setSize (800, 600);
    
    // Some platforms require permissions to open input channels so request that here
    if (juce::RuntimePermissions::isRequired (juce::RuntimePermissions::recordAudio)
        && ! juce::RuntimePermissions::isGranted (juce::RuntimePermissions::recordAudio))
    {
        juce::RuntimePermissions::request (juce::RuntimePermissions::recordAudio,
                                           [&] (bool granted) { setAudioChannels (granted ? 2 : 0, 2); });
    }
    else
    {
        // Specify the number of input and output channels that we want to open
        setAudioChannels (2, 2);
    }
    
    context.setState(&mainMenu);
    startTimer(100);
    
    setWantsKeyboardFocus(true);
    getTopLevelComponent()->addKeyListener(this);
}

MainComponent::~MainComponent()
{
    // This shuts down the audio device and clears the audio source.
    shutdownAudio();
}

//==============================================================================
void MainComponent::prepareToPlay (int samplesPerBlockExpected, double sampleRate)
{
    // This function will be called when the audio device is started, or when
    // its settings (i.e. sample rate, block size, etc) are changed.
    
    // You can use this function to initialise any resources you might need,
    // but be careful - it will be called on the audio thread, not the GUI thread.
    
    // For more details, see the help for AudioProcessor::prepareToPlay()
}

void MainComponent::getNextAudioBlock (const juce::AudioSourceChannelInfo& bufferToFill)
{
    // Your audio-processing code goes here!
    
    // For more details, see the help for AudioProcessor::getNextAudioBlock()
    
    // Right now we are not producing any data, in which case we need to clear the buffer
    // (to prevent the output of random noise)
    //    bufferToFill.clearActiveBufferRegion();
    //    if (listener == nullptr) return;
    int outputChannelsNumber = bufferToFill.buffer->getNumChannels();
    
    // get the audio samples to redirect to the audio output (numSamples represents the total number of frames needed to be played):
    //    auto* samplesInline = listener->getNextAudioSamples(bufferToFill.numSamples, outputChannelsNumber);
    float phaseIncrement = 440.0f / 48000.0f;
    //    get
    
    float temp_phase;
    // map the block of audio frames stored in samplesInline to the audio output:
    for (auto channel = 0 ; channel < outputChannelsNumber ; channel++)
    {
        temp_phase = phase;
        // get a pointer to the start sample in the buffer for this audio output channel :
        auto* buffer = bufferToFill.buffer->getWritePointer(channel, bufferToFill.startSample);
        
        // fill the required number of samples :
        for (auto a = 0 ; a < bufferToFill.numSamples ; a++)
        {
            buffer[a] = sin(2 * M_PI * temp_phase);
            
            temp_phase += phaseIncrement;
            if(temp_phase >= 1.0f)
                temp_phase -= 1.0f;
            
        }
    }
    phase = temp_phase;
}

void MainComponent::releaseResources()
{
    // This will be called when the audio device stops, or when it is being
    // restarted due to a setting change.
    
    // For more details, see the help for AudioProcessor::releaseResources()
}

//==============================================================================
void MainComponent::paint (juce::Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));
    g.drawRect(getWidth()/2.0f, getHeight()/2.0f, 10.0f, 10.0f);
    // You can add your drawing code here!
//    display.paint(g);
    context.paint(g);
    Display::paint(g);
}

void MainComponent::timerCallback()
{
    repaint();
};

void MainComponent::mouseDown(const juce::MouseEvent &event) {
    //    DBG("print"+event.getMouseDownScreenX());
    printf("x=%d, y=%d\n", event.getMouseDownX(), event.getMouseDownY());
    
}

bool MainComponent::keyPressed(const juce::KeyPress &key, juce::Component *originatingComponent) {
    return context.handleKeyPress(key);
}

void MainComponent::resized()
{
    // This is called when the MainContentComponent is resized.
    // If you add any child components, this is where you should
    // update their positions.
}
