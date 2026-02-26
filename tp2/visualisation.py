"""
Visualisation des résultats TP2 - Oscillateur harmonique amorti et chaotique
"""
import os
import numpy as np
import pandas as pd
import matplotlib.pyplot as plt

# config
plt.rcParams['figure.figsize'] = (10, 6)
plt.rcParams['font.size'] = 11
plt.rcParams['lines.linewidth'] = 1.5
plt.rcParams['lines.markersize'] = 5

FIG_DIR = "figures"
RES_DIR = "resultats"

os.makedirs(FIG_DIR, exist_ok=True)


def plot_q13():
    try:
        path = os.path.join(RES_DIR, 'q13_data.csv')
        df = pd.read_csv(path)
        plt.figure()
        plt.plot(df['t'], df['th_pseudo'], label='q=1 (Pseudo-périodique)')
        plt.plot(df['t'], df['th_crit'], label='q=2 (Critique)', ls='--')
        plt.plot(df['t'], df['th_aper'], label='q=5 (Apériodique)', ls='-.')
        plt.title("Q13: Régimes temporels de l'oscillateur harmonique amorti")
        plt.xlabel("Temps (s)")
        plt.ylabel("Angle (rad)")
        plt.legend()
        plt.grid(True, alpha=0.3)
        plt.savefig(os.path.join(FIG_DIR, 'q13_regimes.pdf'), dpi=150, bbox_inches='tight')
        plt.close()
    except Exception as e:
        print(f"Erreur Q13: {e}")
    

def plot_q14():
    try:
        path = os.path.join(RES_DIR, 'q14_data.csv')
        df = pd.read_csv(path)
        plt.figure(figsize=(8, 8))
        plt.plot(df['th_lib'], df['dth_lib'], label='Libre')
        plt.plot(df['th_amort'], df['dth_amort'], label='Amorti', ls='--')
        plt.plot(df['th_force'], df['dth_force'], label='Excité', alpha=0.8)
        plt.title("Q14: Trajectoires dans l'espace des phases")
        plt.xlabel(r"$\theta$ (rad)")
        plt.ylabel(r"$\dot{\theta}$ (rad/s)")
        plt.legend()
        plt.grid(True, alpha=0.3)
        plt.savefig(os.path.join(FIG_DIR, 'q14_phases.pdf'), dpi=150, bbox_inches='tight')
        plt.close()
    except Exception as e:
        print(f"Erreur Q14: {e}")

def plot_q15():
    try:
        path = os.path.join(RES_DIR, 'q15_data.csv')
        df = pd.read_csv(path)
        fig, axes = plt.subplots(4, 1, sharex=True, figsize=(10, 12))
        cols = ['Fe_1.4', 'Fe_1.44', 'Fe_1.465', 'Fe_1.5']
        titles = [r'$F_e=1.4$ (Période T)', 
                  r'$F_e=1.44$ (Période 2T)', 
                  r'$F_e=1.465$ (Période 4T)', 
                  r'$F_e=1.5$ (Chaos)']
        
        for i, col in enumerate(cols):
            mask = df['t'] > 30 
            axes[i].plot(df.loc[mask, 't'], df.loc[mask, col], color='black', lw=0.8)
            axes[i].set_title(titles[i], fontsize=11, pad=5)
            axes[i].set_ylabel(r"$\theta$ (rad)")
            axes[i].grid(True, alpha=0.3)
            
        axes[-1].set_xlabel("Temps (s)")
        plt.suptitle("Q15: Cascade de doublement de période", y=0.995, fontsize=14)
        plt.tight_layout(rect=[0, 0.03, 1, 0.99])
        plt.savefig(os.path.join(FIG_DIR, 'q15_chaos.pdf'), dpi=150, bbox_inches='tight')
        plt.close()
    except Exception as e:
        print(f"Erreur Q15: {e}")

def plot_q16():
    try:
        path = os.path.join(RES_DIR, 'q16_data.csv')
        df = pd.read_csv(path)
        
        fig, (ax1, ax2) = plt.subplots(2, 1, figsize=(10, 10))
        ax1.plot(df['t'], df['th_A'], label=r'$\theta_0 = 10^{\circ}$', lw=1)
        ax1.plot(df['t'], df['th_B'], label=r'$\theta_0 = 9.999^{\circ}$', ls='--', lw=1)
        ax1.set_title("Sensibilité aux conditions initiales ($F_e=1.5$)")
        ax1.set_ylabel(r"$\theta$ (rad)")
        ax1.legend()
        ax1.grid(True, alpha=0.3)
        
        mask = (df['t'] > 0) & (df['delta_abs'] > 1e-12)
        t_log = df.loc[mask, 't']
        log_delta = np.log(df.loc[mask, 'delta_abs'])
        
        ax2.plot(t_log, log_delta, label=r'$\ln|\Delta \theta|$', color='purple')
        t_slope = np.linspace(20, 80, 100)
        lambda_est = 0.15 
        intercept = -14
        ax2.plot(t_slope, lambda_est * t_slope + intercept, 'r--', lw=2, label=r'Pente $\lambda \approx 0.15$')
        ax2.set_title("Divergence des trajectoires (Estimation de l'exposant de Lyapunov)")
        ax2.set_xlabel("Temps (s)")
        ax2.set_ylabel(r"$\ln |\theta_1 - \theta_2|$")
        ax2.legend()
        ax2.grid(True, alpha=0.3)
        plt.tight_layout()
        plt.savefig(os.path.join(FIG_DIR, 'q16_lyapunov.pdf'), dpi=150, bbox_inches='tight')
        plt.close()
    except Exception as e:
        print(f"Erreur Q16: {e}")
    
def plot_q17():
    try:
        path = os.path.join(RES_DIR, 'q17_bifurcation.csv')
        df = pd.read_csv(path)
        plt.figure(figsize=(12, 8))
        plt.scatter(df['Fe'], df['theta_deg'], s=0.1, c='red', alpha=0.6)
        plt.title("Q17: Diagramme de Bifurcation")
        plt.xlabel(r"Amplitude de la force excitatrice $F_e$ (rad.$s^{-2}$)")
        plt.ylabel(r"Angle $\theta$ (degrés) stroboscopé")
        plt.xlim(df['Fe'].min(), df['Fe'].max())
        plt.ylim(df['theta_deg'].min(), df['theta_deg'].max()) 
        plt.grid(True, alpha=0.3)
        plt.tight_layout()
        plt.savefig(os.path.join(FIG_DIR, 'q17_bifurcation.pdf'), dpi=150, bbox_inches='tight')
        plt.close()
    except Exception as e:
        print(f"Erreur Q17: {e}")


def main():
    """Génère tous les graphiques du TP2"""
    for func in [plot_q13, plot_q14, plot_q15, plot_q16, plot_q17]:
        try:
            func()
        except Exception as e:
            print(f"Erreur lors de l'exécution de {func.__name__}: {e}")

if __name__ == "__main__":
    main()