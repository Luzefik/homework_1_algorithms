
import subprocess
import sys
from pathlib import Path

ROOT = Path(__file__).resolve().parent
BUILD_DIR = ROOT / 'build'
BIN = ROOT / 'bin' / 'run_all'
RESULTS_DIR = ROOT / 'bench_results'

def run(cmd):
    print('> ' + ' '.join(cmd))
    subprocess.run(cmd, check=True)

def main():
    try:

        run(['cmake', '-S', str(ROOT), '-B', str(BUILD_DIR)])

        run(['cmake', '--build', str(BUILD_DIR), '--', '-j', '4'])

        if not BIN.exists():
            print('Error: binary not found at', BIN)
            sys.exit(1)
        run([str(BIN)])

        pngs = sorted(RESULTS_DIR.glob('*.png'))
        if not pngs:
            print('No PNG graphs found in', RESULTS_DIR)
            print('You can re-run plot_results.py manually: python3 plot_results.py --ops bench_results/ops_results.csv --sort bench_results/sorting_results.csv --out_dir bench_results --split')
            return

        print('\nGenerated graphs:')
        for p in pngs:
            print(' -', p)

        # On macOS open the images; otherwise just print paths
        if sys.platform == 'darwin':
            for p in pngs:
                subprocess.run(['open', str(p)])
        else:
            print('\nTo view graphs, open the files above with your image viewer.')

    except subprocess.CalledProcessError as e:
        print('Command failed with return code', e.returncode)
        sys.exit(e.returncode)

if __name__ == '__main__':
    main()
