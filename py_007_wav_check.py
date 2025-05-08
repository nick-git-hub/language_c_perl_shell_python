import numpy as np
from scipy.io import wavfile
import sys

def detect_tone_segments_and_freq(filename):
    fs, data = wavfile.read(filename)
    print(f"讀取檔案：{filename}")
    print(f"取樣率：{fs} Hz")

    # 若是立體聲，取一聲道
    if data.ndim > 1:
        data = data[:, 0]
    data = data.astype(float)

    # 掃描參數
    window_size = int(fs * 0.05)  # 50ms
    step_size = int(fs * 0.01)    # 10ms
    threshold = 500               # 判定有聲音的振幅門檻
    tone_present = []

    for start in range(0, len(data) - window_size, step_size):
        window = data[start:start+window_size]
        if np.max(np.abs(window)) > threshold:
            tone_present.append(True)
        else:
            tone_present.append(False)

    tone_present = np.array(tone_present)

    # 偵測 On/Off 時間點
    changes = np.diff(tone_present.astype(int))
    on_idxs = np.where(changes == 1)[0]
    off_idxs = np.where(changes == -1)[0]

    # 邊界修正
    if tone_present[0]:
        on_idxs = np.insert(on_idxs, 0, 0)
    if len(off_idxs) < len(on_idxs):
        off_idxs = np.append(off_idxs, len(tone_present) - 1)

    print(f"\n--- Tone Segments with Main Frequency ---")
    for on_i, off_i in zip(on_idxs, off_idxs):
        start_sample = on_i * step_size
        end_sample = (off_i + 1) * step_size
        segment = data[start_sample:end_sample]

        # Zero-padding for high resolution FFT
        N = 8192
        fft = np.abs(np.fft.rfft(segment, n=N))
        freqs = np.fft.rfftfreq(N, d=1/fs)

        peak_idx = np.argmax(fft)
        dominant_freq = freqs[peak_idx]

        on_time = start_sample / fs
        off_time = end_sample / fs
        duration = off_time - on_time

        print(f"ON: {on_time:.2f}s, OFF: {off_time:.2f}s, Duration: {duration:.2f}s, 主頻率: {dominant_freq:.2f} Hz")

if __name__ == "__main__":
    if len(sys.argv) < 2:
        print("用法: python3 detect_tone_freq.py yourfile.wav")
    else:
        detect_tone_segments_and_freq(sys.argv[1])

