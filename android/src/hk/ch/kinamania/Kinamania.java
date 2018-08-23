//
// Kinamania.java
//

package hk.ch.kinamania;

import android.os.Bundle;
import android.os.Vibrator;
import android.content.Context;
import android.media.AudioManager;

public class Kinamania extends org.qtproject.qt5.android.bindings.QtActivity {
    public static Vibrator m_vibrator;
    public static Kinamania m_instance;

    public Kinamania() {
        m_instance = this;
    }

    @Override
    public void onCreate(Bundle savedInstanceState) {
        this.setVolumeControlStream(AudioManager.STREAM_MUSIC);
        super.onCreate(savedInstanceState);
    }

    public static void vibrate(int x) {
        if (m_vibrator == null) {
            if (m_instance != null) {
              m_vibrator = (Vibrator) m_instance.getSystemService(Context.VIBRATOR_SERVICE);
              m_vibrator.vibrate(x);
            }
        } else {
            m_vibrator.vibrate(x);
        }
    }
}
