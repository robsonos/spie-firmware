const releaseNotesGeneratorOptions = {
  writerOpts: {
    transform: (commit, context) => {
      let discard = true;
      const notes = commit.notes.map((note) => {
        discard = false;

        return {
          ...note,
          title: 'BREAKING CHANGES',
        };
      });

      let type = commit.type;

      if (commit.type === 'breaking') {
        type = 'Breaking :boom:';
      } else if (commit.type === 'feat') {
        type = 'Features :sparkles:';
      } else if (commit.type === 'fix') {
        type = 'Bug Fixes :bug:';
      } else if (commit.type === 'refactor') {
        type = 'Code Refactoring :hammer:';
      } else if (commit.type === 'config') {
        type = 'Config :wrench:';
      } else if (commit.type === 'test') {
        type = 'Tests :rotating_light:';
      } else if (commit.type === 'docs') {
        type = 'Documentation :books:';
      } else if (commit.type === 'build') {
        type = 'Build System :hammer_and_wrench:';
      } else if (commit.type === 'perf') {
        type = 'Performance Improvements :rocket:';
      } else if (commit.type === 'chore') {
        type = 'Chores :gear:';
      } else if (commit.type === 'style') {
        type = 'Style :art:';
      } else if (commit.type === 'ci') {
        type = 'Continuous Integration :loop:';
      }

      const scope = commit.scope === '*' ? '' : commit.scope;
      const shortHash = typeof commit.hash === 'string' ? commit.hash.substring(0, 7) : commit.shortHash;

      const issues = [];
      let subject = commit.subject;

      if (typeof subject === 'string') {
        let url = context.repository ? `${context.host}/${context.owner}/${context.repository}` : context.repoUrl;
        if (url) {
          url = `${url}/issues/`;
          // Issue URLs.
          subject = subject.replace(/#([0-9]+)/g, (_, issue) => {
            issues.push(issue);
            return `[#${issue}](${url}${issue})`;
          });
        }
        if (context.host) {
          // User URLs.
          subject = subject.replace(/\B@([a-z0-9](?:-?[a-z0-9/]){0,38})/g, (_, username) => {
            if (username.includes('/')) {
              return `@${username}`;
            }

            return `[@${username}](${context.host}/${username})`;
          });
        }
      }

      // remove references that already appear in the subject
      const references = commit.references.filter((reference) => !issues.includes(reference.issue));

      return {
        notes,
        type,
        scope,
        shortHash,
        subject,
        references,
      };
    },
    groupBy: 'type',
    commitGroupsSort: (a, b) => {
      const order = [
        'breaking',
        'feat',
        'fix',
        'perf',
        'refactor',
        'build',
        'ci',
        'test',
        'docs',
        'chore',
        'config',
        'style',
      ];
      return order.indexOf(a.title) - order.indexOf(b.title);
    },
    commitsSort: ['scope', 'subject'],
  },
};

module.exports = {
  branches: ['main'],
  plugins: [
    '@semantic-release/commit-analyzer',
    ['@semantic-release/release-notes-generator', releaseNotesGeneratorOptions],
    [
      '@semantic-release/changelog',
      {
        changelogFile: 'CHANGELOG.md',
      },
    ],
    [
      '@semantic-release/exec',
      {
        prepareCmd: 'echo ${nextRelease.version} > VERSION && pio run -e uno',
      },
    ],
    [
      '@semantic-release/git',
      {
        assets: ['CHANGELOG.md'],
      },
    ],
    [
      '@semantic-release/github',
      {
        successComment: false,
        failTitle: false,
        assets: ['dist/**'],
      },
    ],
  ],
};
