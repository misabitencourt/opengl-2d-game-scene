#include <sndfile.h>
#include <portaudio.h>
#include "sound.h"

#define FRAMES_PER_BUFFER   (256000)

// void exec_wav(char * s) {}

static int callback(const void *input, void *output,
                    unsigned long frame_count,
                    const PaStreamCallbackTimeInfo* time_info,
                    PaStreamCallbackFlags status_flags,
                    void *user_data);

PaStream *sound_stream;
callback_data_s sound_data;

static void exec_wav(char * wav_file)
{
    // TODO create loader
    printf(">>>>>>> %s\n", wav_file);
    SNDFILE *file;
    PaError error;
            
    /* Open the soundfile */
    sound_data.filename = wav_file;
    sound_data.file = sf_open(wav_file, SFM_READ, &sound_data.info);
    if (sf_error(sound_data.file) != SF_ERR_NO_ERROR)
    {
        fprintf(stderr, "[Sound] - %s\n", sf_strerror(sound_data.file));
        fprintf(stderr, "[Sound] - %s\n", file);
        return;
    }
    
    /* init portaudio */
    error = Pa_Initialize();
    if(error != paNoError)
    {
        fprintf(stderr, "[Sound] - Problem initializing\n");
        return;
    }
    
    /* Open PaStream with values read from the file */
    error = Pa_OpenDefaultStream(&sound_stream,
                                 0,
                                 2,
                                 paFloat32,
                                 sound_data.info.samplerate,
                                 FRAMES_PER_BUFFER,
                                 callback,
                                 &sound_data);
    if (error != paNoError)
    {
        fprintf(stderr, "Problem opening Default Stream\n");
        return;
    }
    
    /* Start the stream */
    error = Pa_StartStream(sound_stream);
    if (error != paNoError)
    {
        fprintf(stderr, "Problem opening starting Stream\n");
        return;
    }
}

static
int
callback
    (const void                     *input
    ,void                           *output
    ,unsigned long                   frame_count
    ,const PaStreamCallbackTimeInfo *time_info
    ,PaStreamCallbackFlags           status_flags
    ,void                           *user_data
    )
{
    float           *out;
    callback_data_s *p_data = (callback_data_s*)user_data;
    sf_count_t       num_read;

    out = (float*)output;
    p_data = (callback_data_s*)user_data;

    /* clear output buffer */
    memset(out, 0, sizeof(float) * frame_count * 2);

    /* read directly into output buffer */
    num_read = sf_read_float(p_data->file, out, frame_count * 2);
    
    /*  If we couldn't read a full frame_count of samples we've reached EOF */
    if (num_read < frame_count)
    {
        return paComplete;
    }
    
    return paContinue;
}