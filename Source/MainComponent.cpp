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
//        setAudioChannels(1, 1);
    }

//    context.setState(&mainMenu);
//    context.setState(&wavetableModeMenu);
//    enterNameMenu.setBackState(&fxMenu);

    abEngine.Init();
    wavetableEngine.Init();
    matrixEngine.Init();
    drumEngine.Init();

    context.setState(&ioConfigurationMenu);
    context.setEngine(&abEngine);

    effect_manager.Init();
    effect_manager.setEffect(&bypass);
//    fx_engine.Init();
    
    startTimer(16); // 60 / second.  1000/60
//    startTimer(10.666);
    
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
    //    get
    
    // map the block of audio frames stored in samplesInline to the audio output:
    int size = bufferToFill.numSamples;
    float out[size];
    float subosc_out[size];

    adc.handleKeyPress();

    uint16_t tune = adc.getChannelProcessed(0);
    uint16_t fx_amount = adc.getChannelProcessed(1);
    uint16_t fx = adc.getChannelProcessed(2);
    uint16_t morph = adc.getChannelProcessed(3);
    
    context.getEngine()->Render(out, out, size, tune, fx_amount, fx, morph);
    suboscillator.Render(subosc_out, subosc_out, size, tune, fx_amount, fx, morph);
    
    int16_t sample_data = std::clamp<int16_t>(context.getEngine()->GetSine(phase) * 2048.0f + 2048.0f, 0, 4095);
    adc.setChannel(Adc::ADC_CHANNEL_PITCH_CV, sample_data);
    adc.setChannel(Adc::ADC_CHANNEL_FX_AMOUNT_CV, 2048);
    adc.setChannel(Adc::ADC_CHANNEL_FX_CV, 2048);
    adc.setChannel(Adc::ADC_CHANNEL_MORPH_CV, 2048);

    if(context.getState() == &ioConfigurationMenu) {
        ioConfigurationMenu.UpdateWaveform();
    }
           
    for (auto channel = 0 ; channel < outputChannelsNumber ; channel++)
    {
        // get a pointer to the start sample in the buffer for this audio output channel :
        auto* buffer = bufferToFill.buffer->getWritePointer(channel, bufferToFill.startSample);

        for (auto a = 0 ; a < bufferToFill.numSamples ; a++)
        {
            if(channel == 0) {
                float phase_increment = 1.0f / 48000.0f;
                phase += phase_increment;
                if(phase >= 1.0f)
                    phase -= 1.0f;
            }
            buffer[a] = (user_settings.getSubOscMix() / 100.0f) * out[a] + (1.0f - user_settings.getSubOscMix() / 100.0f) * subosc_out[a];
        }
    }
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
    popup.paint(g);
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
    printf("%d\n", key.getKeyCode());
    bool pass = popup.handleKeyPress(key);
    if(!pass) {
        pass = context.handleKeyPress(key);
    }
    return pass;
}

void MainComponent::resized()
{
    // This is called when the MainContentComponent is resized.
    // If you add any child components, this is where you should
    // update their positions.
}
