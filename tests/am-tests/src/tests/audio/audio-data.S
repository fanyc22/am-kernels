#ifdef __aarch64__
// TODO: migrant for ARM
.data
.global audio_payload, audio_payload_end
.p2align 3
audio_payload:
.incbin "src/tests/audio/little-star.pcm"
audio_payload_end:
#else
.section .data
.global audio_payload, audio_payload_end
.p2align 3
audio_payload:
.incbin "src/tests/audio/little-star.pcm"
audio_payload_end:
#endif