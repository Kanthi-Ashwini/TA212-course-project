# Pushing this to GitHub

Nothing is committed yet — no `git init` has been run, so rename or edit freely
first.

1. Create an empty repo on GitHub named `TA212-dual-axis-solar-tracker`
   (no README, no .gitignore — this folder has both).

2. From inside this folder:

```bash
git init
git add .
git commit -m "TA212 dual-axis solar tracker: Arduino drive control"
git branch -M main
git remote add origin https://github.com/<user>/TA212-dual-axis-solar-tracker.git
git push -u origin main
```

3. Put the resulting URL into `../ta212-resume-snippet.tex`, replacing `<user>`.

## Before pushing

- The sketches are **byte-identical** to the original `code.txt` / `code-2.txt`,
  only renamed to the `.ino` convention Arduino requires (sketch must sit in a
  folder of the same name). No behaviour was changed.
- `README.md` and `docs/KNOWN_ISSUES.md` state plainly that there is no light
  sensing. That is deliberate — it is accurate, and a reviewer who opens the
  code will see it immediately. If the LDR/feedback code exists somewhere else,
  add it and both files should be rewritten.
- Add a photo of the built mount to `docs/` if one exists; it is the single
  biggest improvement available to this repo.
- Fill in the instructor, semester and team members at the top of `README.md`.
