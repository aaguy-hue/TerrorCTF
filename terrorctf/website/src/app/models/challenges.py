from sqlalchemy import CheckConstraint
from app.extensions import db


class Problem(db.Model):
    id = db.Column(db.Integer, primary_key=True)
    name = db.Column(db.String(100))
    description = db.Column(db.Text)
    category = db.Column(db.String(50))

    __table_args__ = (
        CheckConstraint(
            category.in_(['crypto', 'web', 'pwn', 'rev', 'misc']),
            name='valid_problem_category'
        ),
    )

    # the Team model will make a field called teams_that_solved

    def __repr__(self):
        return f'<Problem "{self.name}">'
    
